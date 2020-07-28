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
        SERVER_ERROR = 50,
        CLIENT_LOGOUT = 201,
        ROOM_RESPONSE = 100,
        ROOM_PLAYERS_RESPONSE = 101,
        ROOM_LOGIN = 102,
        ROOM_CREATE = 103,
        ROOM_PLAYERS = 104,
        ROOMS = 105,
        STATISTICS = 40,
    }

    public static class Socket_Extension
    {
        public static byte[] ReceiveAll(this Socket socket)
        {
            var buffer = new List<byte>();

            while (socket.Available > 0)
            {
                var currByte = new Byte[1];
                var byteCounter = socket.Receive(currByte, currByte.Length, SocketFlags.None);

                if (byteCounter.Equals(1))
                {
                    buffer.Add(currByte[0]);
                }
            }

            return buffer.ToArray();
        }


        public static string ToASCIIStr(this byte[] arr)
        {
            return Encoding.ASCII.GetString(arr);
        }

    }


    public class socket_client
    {
        string ip = "";
        int port = 0;

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

                try
                {
                    tempSocket.Connect(ipe);
                }
                catch (Exception)
                {

                }

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

        public JObject SocketSendReceive(JObject request, int code)
        {
            return SocketSendReceive(request.ToString(), code);
        }


        /*this function gets a request and a code and returns the answer from the server in json form*/
        public JObject SocketSendReceive(string request, int code)
        {

            if (this.socket == null)
                throw new Exception("Connection fail");

            //the code part in the protocol is 1 byte
            byte[] code_part = new byte[1];
            //code_part[0] = BitConverter.GetBytes(code)[0]; //converting int to byte 
            code_part[0] = (byte)code; //converting int to byte 

            Console.WriteLine(code);
            Console.WriteLine((byte)code);
            Console.WriteLine((char)code);



            byte[] length_part = BitConverter.GetBytes(request.Length);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(length_part);

            // code + len + data
            byte[] msg = code_part.Concat(length_part).Concat(Encoding.ASCII.GetBytes(request)).ToArray();

            Console.WriteLine(BitConverter.ToString(msg).Replace('-', ' '));

            // Send the request to the server.
            this.socket.Send(msg);


            byte[] temp = new byte[5];
            // Receive from the server the first five bytes. 
            this.socket.Receive(temp, 5, 0);

            string response = socket.ReceiveAll().ToASCIIStr();

            Console.WriteLine(response);

            return JObject.Parse(response);

        }



        public bool login(string name, string password)
        {
            var request = new JObject();
            request["username"] = name;
            request["password"] = password;

            dynamic d = SocketSendReceive(request, (int)CODES.CLIENT_LOGIN);

            return d.status == 1;

        }

        public bool signup(string name, string password, string email)
        {
            var request = new JObject();
            request["username"] = name;
            request["password"] = password;
            request["email"] = email;

            dynamic d = SocketSendReceive(request, (int)CODES.CLIENT_SIGNUP);

            return d.status == 1;

        }


        public int CreateRoom(string RoomName, int QuetionCount = 5, int AnswerTimeout = 20)
        {
            var request = new JObject();
            request["roomName"] = RoomName;
            request["maxUsers"] = 4; // GUI limitation
            request["questionCount"] = QuetionCount;
            request["answerTimeout"] = AnswerTimeout;


            dynamic d = SocketSendReceive(request, (int)CODES.ROOM_CREATE);


            return d.roomId;
        }

        public int GetPlayersInRoom(int RoomID)
        {

            var request = new JObject();
            request["roomId"] = RoomID;

            dynamic d = SocketSendReceive(request, (int)CODES.ROOM_PLAYERS);

            return d.players;
        }


        public bool JoinRoom(int RoomID)
        {
            var request = new JObject();
            request["roomId"] = RoomID;

            dynamic d = SocketSendReceive(request, (int)CODES.ROOM_LOGIN);

            return d.status == 1;
        }


        public List<List<string>> GetAllRooms()
        {

            dynamic d = SocketSendReceive("", (int)CODES.ROOMS);

            return d.rooms.ToObject<List<List<string>>>();

        }

        public List<string> getStats()
        {
            dynamic d = SocketSendReceive("", (int)CODES.STATISTICS);

            return d.statistics.ToObject<List<string>>();
        }



    }
}
