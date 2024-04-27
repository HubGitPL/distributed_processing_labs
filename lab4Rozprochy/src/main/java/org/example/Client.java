package org.example;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;
//klasa klienta z pespektywy klienta
public class Client {
    private static final int PORT = 8000;
    private Socket socket;
    private BufferedReader reader;
    private BufferedWriter writer;
    private String username;

    public Client(Socket socket, String username) throws IOException {
        this.socket = socket;
        this.reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        this.username = username;

    }
    //dziala w glownym watku
    //odczytuje wiadomosci od klienta i wysyla je do serwera
    public void sendMessage() {
        try {
            writer.write(username);
            writer.newLine();
            writer.flush();

            Scanner scanner = new Scanner(System.in);
            while(socket.isConnected()){
                String message = scanner.nextLine();
                writer.write(message + "\n");
                writer.flush();
            }

        } catch (IOException e) {
            stopClient();
            e.printStackTrace();
        }
    }
    //uruchamia nowy watek
    public void listenForMessages(){
        new Thread(new Runnable() {
            @Override
            public void run() {
                String message;
                while(socket.isConnected()){
                    try{
                        message = reader.readLine();
                        if(message != null){
                            System.out.println(message);
                        }
                    } catch (IOException e) {
                        stopClient();
                        throw new RuntimeException(e);
                    }
                }
            }
        }).start();
    }
    public void stopClient() {
        try {
            if (socket != null) {
                socket.close();
            }
            if(reader != null){
                reader.close();
            }
            if(writer != null){
                writer.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("localhost", PORT);
        System.out.println("Connected to server");
        System.out.println("Enter your username: ");
        Scanner scanner = new Scanner(System.in);
        String username = scanner.nextLine();
        Client client = new Client(socket, username);
        client.listenForMessages();
        client.sendMessage();
    }
}