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
        public join_games()
        {
            InitializeComponent();

            //get the players name from the database.
            player_name.Content = "יקיר אורן";

            // add active games. maybe add background thread for active games.

            for (int i = 0; i < 3; i++)
            {
                game new_game = new game(3, "asda", "sadad");

                games.Children.Add(new_game);

            }


        }


    }
}
