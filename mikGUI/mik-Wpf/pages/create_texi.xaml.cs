using System.Linq;
using System.Windows;
using mik_Wpf.app_code;

namespace mik_Wpf
{
    /// <summary>
    /// Interaction logic for create_texi.xaml
    /// </summary>
    public partial class create_texi : Window
    {
        public bool isAdmin;
        public string AdminName;
        public int gameID;
        public MainWindow mainWindow;
        public create_texi(int gameID, string AdminName,bool isAdmin = false)
        {
            this.gameID = gameID;
            this.isAdmin = isAdmin;
            this.AdminName = AdminName;
            InitializeComponent();

            if (!this.isAdmin)
            {
                this.submit.Visibility = Visibility.Hidden;
            }

        }

        private void exit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();

        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {

            mainWindow = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();

            if (mainWindow != null)
            {
                driver_lbl.Text = mainWindow.username;
            }


            //get list of connected users from the data base.

            // when a new player joins add him to the list.


            
            getPlayers();
            //mainWindow.Client.socket.ReceiveAll(); // wait for a messge from the server (the messge will be that a new client has join the room and this client should update the )




        }


        public void getPlayers()
        {
            players.Children.Clear();

            var d = mainWindow.Client.GetPlayersInRoom(this.gameID);

            driver_lbl.Text = d[0];
            
            d.RemoveAt(0);

            foreach (var name in d)
            {
                var new_game = new lobby_user(name);
                players.Children.Add(new_game);

            }
        }

        private void submit_Click(object sender, RoutedEventArgs e)
        {
            //only the admin can start the game

            //when the admin clickes the button the other players should be moved to the game room.

            //genrate a new game id;


            // send start game request.

            _gameFrame.Navigate(new game(gameID));


        }

    }
}
