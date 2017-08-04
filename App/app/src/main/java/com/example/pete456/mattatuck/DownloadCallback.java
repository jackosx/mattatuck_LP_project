package com.example.pete456.mattatuck;

/**
 * Created by pete456 on 8/2/17.
 */

public interface DownloadCallback<T>
{
    interface Progress{
        int ERROR = -1;
        int CONNECT_SUCCESS = 0;
        int GET_INPUT_STREAM_SUCCESS = 1;
        int PROCESS_INPUT_STREAM_IN_PROGRESS = 2;
        int PROCESS_INPUT_STREAM_SUCCESS = 3;

    }
}
