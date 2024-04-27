package org.example;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;

//Klasa reprezentujaca klienta polaczonego z serwerem
//kazdy clientHandler jest uruchamiany w nowym watku
public class ClientHandler implements Runnable{
    private Socket socket;
    private BufferedReader reader;
    private BufferedWriter writer;
    private String username;
    private boolean isFirstMessage = true;

    public static ArrayList<ClientHandler> clients = new ArrayList<>();

    public ClientHandler(Socket socket) throws IOException {
        this.socket = socket;
        this.reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        clients.add(this);
    }
    //metoda uruchamiana w nowym watku dla kazdego klienta
    //odczytuje wiadomosci od klienta i przekazuje je do innych klientow
    @Override
    public void run() {
        String message;
        while(socket.isConnected()){
            try{
                message = reader.readLine();
                if(message != null){
                    if(isFirstMessage){
                        username = message;
                        isFirstMessage = false;
                    } else {
                        broadcastMessage(message);
                    }
                }
            } catch (IOException e) {
                stopClient();
                throw new RuntimeException(e);
            }
        }
    }
    //wysyla wiadomosc do wszystkich klientow
    public void broadcastMessage(String message) throws IOException {
        for(ClientHandler client : clients){
            if(client != this){
                client.writer.write(username + ": " + message + "\n");
                client.writer.flush();
            }
        }
    }

    public void removeClientHandler(ClientHandler client){
        clients.remove(client);
        System.out.println("Client disconnected from port " + client.socket.getPort());
    }
    public void stopClient() {
        removeClientHandler(this);
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
}