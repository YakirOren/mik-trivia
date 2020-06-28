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


        public void CreateRoom()
        {
            //get the info from the user.

            //user name
            // user need to selct what kind of questions to be asked i.e destination.


            game_msg new_game = new game_msg(0, parentWindow.username);

            games.Children.Add(new_game);

        }

        public void LookForActiveGames()
        {
            while (true)
            {

            }
        }

        private void join_Click(object sender, RoutedEventArgs e)
        {
            // genrate a new game id;
            create_texi dd = new create_texi(1, true);
            CreateRoom();
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

            }

            // add active games. maybe add background thread for active games.
            CreateRoom();
            CreateRoom();
        }
    }
}
