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


        public JObject SocketSendReceive(string request, int code)
        {

            Byte[] msg = Encoding.ASCII.GetBytes(code.ToString()).Concat(Encoding.ASCII.GetBytes(request.Length.ToString())).Concat(Encoding.ASCII.GetBytes(request)).ToArray();


            Byte[] bytesReceived = new Byte[256];



            string response = "";

            if (this.socket == null)
                throw new Exception("Connection fail");

            // Send request to the server.
            this.socket.Send(msg, msg.Length, 0);



            int bytes = 0;

            // Receive the server 


            Byte[] temp = new Byte[5];

            //Console.WriteLine(this.socket.Receive(temp, 5, 0));


            do
            {
                bytes = this.socket.Receive(bytesReceived, bytesReceived.Length, 0);
                response = response + Encoding.ASCII.GetString(bytesReceived, 0, bytes);

                foreach (var item in bytesReceived)
                {
                    Console.WriteLine(item);
                }

                Console.WriteLine(bytes);
                Console.WriteLine(response);
            }
            while (bytes > 0);
            



            JObject json = JObject.Parse(response);

            return json;
        }



        public bool login(string name, string password)
        {

            var content = "{ \"username\": \"" + name + "\",\"password\": \"" + password + "\"}";

            dynamic d = SocketSendReceive(content, (int)CODES.CLIENT_LOGIN);

            Console.WriteLine(d);

            return d.status == 1;

        }

        public bool signup(string name, string password, string email)
        {

            string content = (int)CODES.CLIENT_SIGNUP + "{ \"username\": \"" + name + "\",\"password\": \"" + password + "\", \"email\": \"" + email + "\"}";

            dynamic d = SocketSendReceive(content, (int)CODES.CLIENT_SIGNUP);

            return d.status == 1;

        }





    }
}
