using System.Linq;
using System.Windows;


namespace mik_Wpf
{
    /// <summary>
    /// Interaction logic for create_texi.xaml
    /// </summary>
    public partial class create_texi : Window
    {
        public bool isAdmin;
        public int gameID;
        public create_texi(int gameID, bool isAdmin = false)
        {
            this.gameID = gameID;
            this.isAdmin = isAdmin;
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

            MainWindow mainWindow = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();

            if (mainWindow != null)
            {
                driver_lbl.Text = mainWindow.username;
            }


            //get list of connected users from the data base.

            // when a new player joins add him to the list.

            players.Children.Add(new lobby_user("yakir"));
            players.Children.Add(new lobby_user("yakir"));
            players.Children.Add(new lobby_user("yakir"));

        }

        private void submit_Click(object sender, RoutedEventArgs e)
        {
            //only the admin can start the game

            //when the admin clickes the button the other players should be moved to the game room.

            //genrate a new game id;


            _gameFrame.Navigate(new game(gameID));


        }

    }
}
