#ifdef MPI_HAO

#include "../include/populationControl.h"

using namespace std;

//Determine the number each thread need to send out to other thread
//send_number_list is the list only in main thread.
void deterSendNumber(int& send_number, vector<int>& send_number_list, const vector<int>& table)
{
    int rank=MPIRank(); int size=MPISize();
 
    if(rank==0) 
    {
        int L=table.size(); int L_chunk=L/size;
        send_number_list=vector<int>(size, 0);

        int j, rank_recv, rank_send;
        for(int i=0; i<L; i++)
        {
            j=table[i];
            rank_recv=i/L_chunk;
            rank_send=j/L_chunk;
            if(rank_send!=rank_recv) send_number_list[rank_send]++;
        }
        //for(int i=0; i<size; i++) cout<<send_number_list[i]<<" "; cout<<endl;
    }
    MPI_Scatter(send_number_list.data(), 1, MPI_INT, &send_number, 1, MPI_INT, 0, MPI_COMM_WORLD);
}


//Determine the send table each thread need to send out, table_send[2*i] is parent, table_send[2*i+1] is child
void deterTableSend(int send_number, const vector<int>& send_number_list, const vector<int>& table, vector<int>& table_send)
{
    int rank=MPIRank(); int size=MPISize();

    int total_send_number=0;
    vector<int> table_send_list;
    vector<int> disp; //first position to be sent in table_send_list
    if(rank==0)
    {
        //Set total_send_number, allocate table_send_list
        total_send_number=0; for(int i=0; i<size; i++) total_send_number+=send_number_list[i];
        table_send_list.resize(2*total_send_number);

        //Set disp
        disp.resize(size); disp[0]=0; for(int i=1; i<size; i++) disp[i]=disp[i-1]+send_number_list[i-1];

        //Set table_send_list
        int L=table.size(); int L_chunk=L/size;
        int j, rank_recv, rank_send;
        vector<int> count=disp;
        for(int i=0; i<L; i++)
        {
            j=table[i];
            rank_recv=i/L_chunk;
            rank_send=j/L_chunk;
            if(rank_send!=rank_recv)
            {
               table_send_list[ count[rank_send]                   ] = j; //Parent
               table_send_list[ count[rank_send]+total_send_number ] = i; //Child
               count[rank_send]++;
            }
        }
    }

    table_send.resize(2*send_number);
    //Scatter Parent
    MPI_Scatterv(table_send_list.data(), send_number_list.data(), disp.data(), MPI_INT, table_send.data(), send_number, MPI_INT, 0, MPI_COMM_WORLD); 
    //Scatter Child
    MPI_Scatterv(table_send_list.data()+total_send_number, send_number_list.data(), disp.data(), MPI_INT, 
                 table_send.data()+send_number, send_number, MPI_INT, 0, MPI_COMM_WORLD);

    //if(MPIRank()==0) {for(int i=0; i<send_number; i++) cout<<table_send[i]<<" "<<table_send[i+send_number]<<endl;}
    //MPIBarrier();
    //if(MPIRank()==1) {for(int i=0; i<send_number; i++) cout<<table_send[i]<<" "<<table_send[i+send_number]<<endl;}
    //MPIBarrier();
    //if(MPIRank()==2) {for(int i=0; i<send_number; i++) cout<<table_send[i]<<" "<<table_send[i+send_number]<<endl;}
    //MPIBarrier();
    //if(MPIRank()==3) {for(int i=0; i<send_number; i++) cout<<table_send[i]<<" "<<table_send[i+send_number]<<endl;}
    //MPIBarrier();
}

//Not all send_number are sent, use the property that receive thread and send thread are ascending
int deterBufSendNumber(int L_chunk, int send_number, const vector<int>& table_send)
{
    int count=0;
    int send_index_bk=-1, recv_rank_bk=-1;
    int send_index, recv_rank;
    for(int i=0; i<send_number; i++)
    {
        send_index = table_send[i]; //Parent
        recv_rank  = table_send[i+send_number]/L_chunk; //Child
        //If send_index==send_index_bk and recv_rank==recv_rank_bk: do not send
        //If send_index!=send_index_bk: send
        //If recv_rank!=recv_rank_bk: send 
        if(send_index!=send_index_bk || recv_rank!=recv_rank_bk )
        {
            count++;
            send_index_bk = send_index;
            recv_rank_bk  = recv_rank;
        }
    }

    return count;
}

//Not all send_number are received, use the property that receive thread and send thread are ascending
int deterBufRecvNumber(const vector<int>& table_recv)
{
    int rank=MPIRank(); int L_chunk=table_recv.size();
    int count=0;
    int send_index_bk=-1;
    int send_index, send_rank;
    for(int i=0; i<L_chunk; i++)
    {
        send_index=table_recv[i];
        send_rank=send_index/L_chunk;
        //If send_rank == rank: do not receive buf
        //When send_rank != rank, if send_index == send_index_bk: do not receive buf, use last received one.
        //Only when send_rank != rank and send_index != send_index_bk receive buf.
        if(send_rank != rank && send_index != send_index_bk)
        {
            count++;
            send_index_bk=send_index;
        }
        
    }
    return count;
}

#endif