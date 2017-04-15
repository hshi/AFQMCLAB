#ifndef AFQMCLAB_POPULATIONCONTROL_H
#define AFQMCLAB_POPULATIONCONTROL_H

#include <iostream>
#include <vector>
#include "../../../../common/mpiHao/include/mpi_fun.h"

//size is MPISize(), only call pop_configuration for one thread
std::vector<int> popConfiguration(int size, const std::vector<double>& weight);

#ifdef MPI_HAO
void deterSendNumber(int& send_number, std::vector<int>& send_number_list, const std::vector<int>& table);
void deterTableSend(int send_number, const std::vector<int>& send_number_list, const std::vector<int>& table, std::vector<int>& table_send);
int deterBufSendNumber(int L_chunk, int send_number, const std::vector<int>& table_send);
int deterBufRecvNumber(const std::vector<int>& table_recv);
#endif

template<class T >
void pop_control(std::vector<T>& walker, const std::vector<int>& table)
{
    int rank=MPIRank(); int size=MPISize(); int L_chunk=walker.size();
    int L=0; if(rank==0) L=table.size(); MPIBcast(L);
    if( (L_chunk*size) !=  L ) {std::cout<<"ERROR!!! Size of table can not be divided by MPISize."<<std::endl; exit(1);}
    if( L_chunk==0 ) return;


#ifdef MPI_HAO
    //Determine table_recv
    std::vector<int> table_recv(L_chunk);
    MPI_Scatter(table.data(), L_chunk, MPI_INT, table_recv.data(), L_chunk, MPI_INT, 0, MPI_COMM_WORLD);

    //Determine the number each thread will send out, send_number_list is the list only in main thread
    int send_number;
    std::vector<int> send_number_list;
    deterSendNumber(send_number, send_number_list, table);

    //Determine_table_send
    std::vector<int> table_send; //Parent is 0~send_number, child is send_number~2*send_number
    deterTableSend(send_number, send_number_list, table, table_send);

    //Determine buf_send_number, and buf_recv_number for each thread.
    //Not all send_number are sent, use the property that receive thread and send thread are ascending
    int buf_send_number=deterBufSendNumber(L_chunk, send_number, table_send);
    int buf_recv_number=deterBufRecvNumber(table_recv);

    //Some parameters for send and recv
    int count, send_index, recv_rank, send_index_bk, recv_rank_bk, send_rank, send_local_index, recv_local_index;
    int Nbuf=(walker[0]).Nbuf;
    std::vector< std::vector<char>  >  buf_send(buf_send_number); 
    std::vector<char> buf_recv_one(Nbuf);
    std::vector< MPI_Request > ISREQ(buf_send_number); 
    std::vector< MPI_Status  > ISSTA(buf_send_number);
    MPI_Status IRSTA;


    //Start to send
    count=0; send_index_bk=-1, recv_rank_bk=-1;
    for(int i=0; i<send_number; i++)
    {
        send_index = table_send[i];
        recv_rank  = table_send[i+send_number]/L_chunk;
        if(send_index!=send_index_bk || recv_rank!=recv_rank_bk )
        {
            send_local_index= send_index- rank*L_chunk;
            recv_local_index= table_send[i+send_number]-recv_rank*L_chunk;

            buf_send[count] = (walker[send_local_index]).pack();
            MPI_Isend( (buf_send[count]).data(), Nbuf, MPI_BYTE, recv_rank, recv_local_index, MPI_COMM_WORLD, ISREQ.data()+count);

            count++;
            send_index_bk   = send_index;
            recv_rank_bk    = recv_rank;
        }
    }

    //Start to receive
    count=0; send_index_bk=-1; recv_local_index=-1;
    for(int i=0; i<L_chunk; i++)
    {
        send_index = table_recv[i];
        send_rank  = send_index/L_chunk;

        if(send_rank == rank) //receive from same rank
        {
            send_local_index=send_index-send_rank*L_chunk; 
            if(i!=send_local_index) walker[i]=walker[send_local_index];
        }
        else //receive from different rank
        {
            if(send_index == send_index_bk)   walker[i]=walker[recv_local_index]; //Use the last received index  
            else  //receive and unpack, make backup
            {
                MPI_Recv(buf_recv_one.data(), Nbuf, MPI_BYTE, send_rank, i, MPI_COMM_WORLD, &IRSTA);
                (walker[i]).unpack(buf_recv_one);

                count++;
                send_index_bk=send_index;
                recv_local_index=i;
            }
        }
    }
    if(count != buf_recv_number) {std::cout<<"Something is wrong in population control, buf_recv_number not consistent! "<<std::endl; exit(1);}


    //Wait
    if(buf_send_number>0) MPI_Waitall(buf_send_number, ISREQ.data(), ISSTA.data() );
    MPIBarrier();
#else
    int j;
    for(int i=0; i<L; i++)
    {
        j=table[i]; //j is the parent 
        if(i!=j) walker[i]=walker[j];
    }
#endif
}

#endif
