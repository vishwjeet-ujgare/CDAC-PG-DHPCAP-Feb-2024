void do_server_work ( int number_of_processes )
{
    const int max_message_length = 256;
    char message [ max_message_length ];
    int src ;
    MPI_Status status ;
    for ( src = 0; src < number_of_processes ; src ++ )
    {
     if ( src != SERVER  _RANK )
    {
   
    MPI_Recv ( message , max_message_length , MPI_CHAR ,
    src , MESSAGE_TAG , MPI_COMM_WORLD ,
    & status );
    printf ( " Received : % s \n " , message );
    }
    }
}
void do_client_work ( int rank )
{
    const int max_message_length = 256;
    char message [ max_message_length ];
    int message_length ;
    
    message_length =sprintf ( message , " Greetings from process % d " , rank );
    message_length ++; /* add one for null char */
    MPI_Send ( message , message_length , MPI_CHAR ,
    SERVER_RANK , MESSAGE_TAG , MPI_COMM_WORLD );
}