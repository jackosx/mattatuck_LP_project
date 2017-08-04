package com.example.pete456.mattatuck;

import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

public class MainActivity extends ActionBarActivity
{
    private TextView serverData;
    public void sendMessage(final TextView test)
    {
        final Handler handler = new Handler();

        Thread thread = new Thread(new Runnable(){
            String st;
            boolean connectable;
            @Override
            public void run() {
                try{
                    Socket s = new Socket("10.1.1.121", 8080);
                    Log.d("yeet","created socket");
                    OutputStream out = s.getOutputStream();
                    PrintWriter output = new PrintWriter(out);
                    output.print("get all");
                    output.flush();
                    BufferedReader input = new BufferedReader(new InputStreamReader(s.getInputStream()));
                    st = input.readLine();

                    runOnUiThread(new Runnable() {
                        @Override
                        public void run()
                        {
                            if(st == "no command")
                            {

                            }else if(st == ""){

                            }else{
                                format();
                            }
                        }
                        public void format()
                        {
                            String formattedInput = "";
                            String formattedPart = "";
                            for(int i = 0; i < st.length(); i++)
                            {
                                if(st.charAt(i) == '|')
                                {
                                    formattedInput += (formattedPart+"\n");
                                    formattedPart = "";
                                }else{
                                    formattedPart+=st.charAt(i);
                                }
                            }
                            test.setText(formattedInput);
                            Log.d("yeet","why cant i work");
                        }
                    });

                    output.close();
                    out.close();
                    s.close();
                }catch(IOException e){
                    e.printStackTrace();
                    Log.d("yeet",e.toString());
                }
            }
            public void test()
            {

            }
        });
        thread.start();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final Button buttonSend = (Button)findViewById(R.id.get_button);
        serverData = (TextView)findViewById(R.id.tv);
        buttonSend.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View view)
            {
                sendMessage(serverData);
            }
        });

    }

}
