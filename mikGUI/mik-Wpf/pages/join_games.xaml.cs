
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace mik_Wpf
{
    /// <summary>
    /// Interaction logic for join_games.xaml
    /// </summary>
    public partial class join_games : Page
    {
        public MainWindow parentWindow;
        public string username;

        public join_games()
        {
            InitializeComponent();
        }


        public int CreateRoom()
        {

            int newRoomId = parentWindow.Client.CreateRoom(username);
            // this send to the server that a new room has been created. 
            //the server will notify all the other clients that a new room has been create which the LookForActiveGames function handels.



            //game_msg new_game = new game_msg(newRoomId, parentWindow.username);

            //games.Children.Add(new_game);

            getGames();

            return newRoomId;
        }

        public void LookForActiveGames()
        {
            while (true)
            {
                parentWindow.Client.GetAllRooms();

                // thread sleep.... for 30 sec?

            }
        }

        private void join_Click(object sender, RoutedEventArgs e)
        {
            int roomId = CreateRoom();
            parentWindow.Client.JoinRoom(roomId);
            create_texi dd = new create_texi(roomId, parentWindow.Client.GetPlayersInRoom(roomId)[0], true);
            parentWindow = Window.GetWindow(this) as MainWindow;

            
            if (parentWindow != null)
            {
                parentWindow.Hide();
                dd.ShowDialog();
                parentWindow.Show();
            }




        }

        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
            parentWindow = Window.GetWindow(this) as MainWindow;

            if (parentWindow != null)
            {
                username = parentWindow.username;
                player_name.Content = username;
                getGames();
            }

            // add active games. maybe add background thread for active games.

        }

        private void stats_Click(object sender, RoutedEventArgs e)
        {
            var dd = new stats();

            if (parentWindow != null)
            {
                //parentWindow.Hide();
                dd.ShowDialog();
                //parentWindow.Show();
            }
        }


        public void getGames()
        {
            games.Children.Clear();

            var d = parentWindow.Client.GetAllRooms().Reverse<List<string>>();

            foreach (var item in d)
            {
                game_msg new_game = new game_msg(int.Parse(item[1]), item[0], int.Parse(item[3]));
                games.Children.Add(new_game);

            }
        }


        private void refresh_Click(object sender, RoutedEventArgs e)
        {
            getGames();

        }
    }
}
