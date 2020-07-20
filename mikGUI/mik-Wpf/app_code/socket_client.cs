using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Net;
using System.Net.Sockets;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using Newtonsoft.Json.Linq;

namespace mik_Wpf.app_code
{
    enum CODES : int
    {
        CLIENT_LOGIN = 200,
        CLIENT_SIGNUP = 204,
        SERVER_ERROR = 500,
        CLIENT_LOGOUT = 201,
        ROOM_RESPONSE = 300,
        ROOM_PLAYERS_RESPONSE = 301,
        ROOM_LOGIN = 302,
        ROOM_CREATE = 303,
        ROOM_PLAYERS = 304,
        ROOMS = 305,
        STATISTICS = 400,
    }
    public class socket_client
    {
        string ip;
        int port;

        Socket socket;

        public socket_client(string ip, int port)
        {
            this.ip = ip;
            this.port = port;

            //create a new connection to the server.
            socket = ConnectSocket();
        }


        public Socket ConnectSocket()
        {
            Socket s = null;
            IPHostEntry hostEntry = null;

            // Get host related information.
            hostEntry = Dns.GetHostEntry(ip);

            // Loop through the AddressList to obtain the supported AddressFamily. This is to avoid
            // an exception that occurs when the host IP Address is not compatible with the address family
            // (typical in the IPv6 case).
            foreach (IPAddress address in hostEntry.AddressList)
            {
                IPEndPoint ipe = new IPEndPoint(address, port);
                Socket tempSocket =
                    new Socket(ipe.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                tempSocket.Connect(ipe);

                if (tempSocket.Connected)
                {
                    s = tempSocket;
                    break;
                }
                else
                {
                    continue;
                }
            }
            return s;
        }


        /*this function gets a request and a code and returns the answer from the server in json form*/
        public JObject SocketSendReceive(string request, int code)
        {

            if (this.socket == null)
                throw new Exception("Connection fail");

            //the code part in the protocol is 1 byte
            byte[] code_part = new byte[1];
            code_part[0] = BitConverter.GetBytes(code)[0]; //converting int to byte 


            byte[] length_part = BitConverter.GetBytes(request.Length);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(length_part);

            // code + len + data
            byte[] msg = code_part.Concat(length_part).Concat(Encoding.ASCII.GetBytes(request)).ToArray();

            Console.WriteLine(BitConverter.ToString(msg).Replace('-',' '));

            // Send the request to the server.
            this.socket.Send(msg);


            byte[] temp = new byte[5];
            // Receive from the server the first five bytes. 
            this.socket.Receive(temp, 5, 0); 


            byte[] bytesReceived = new byte[256];
            int bytes = 0;
            string response = "";

            //THIS ONLY GETS 256 BYTES FROM THE SOCKET

            bytes = this.socket.Receive(bytesReceived);
            response = Encoding.ASCII.GetString(bytesReceived, 0, bytes);

            // should add loop if the message size would be lager then 256.

                        
            Console.WriteLine(response);

            return JObject.Parse(response);

        }



        public bool login(string name, string password)
        {

            var content = "{ \"username\": \"" + name + "\",\"password\": \"" + password + "\"}";


            Console.WriteLine(content);
            dynamic d = SocketSendReceive(content, (int)CODES.CLIENT_LOGIN);

            Console.WriteLine(d);

            return d.status == 1;

        }

        public bool signup(string name, string password, string email)
        {

            string content = "{ \"username\": \"" + name + "\",\"password\": \"" + password + "\", \"email\": \"" + email + "\"}";
            Console.WriteLine(content);
            dynamic d = SocketSendReceive(content, (int)CODES.CLIENT_SIGNUP);
            Console.WriteLine(d);

            return d.status == 1;

        }





    }
}
