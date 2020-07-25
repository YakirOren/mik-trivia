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
    /// Interaction logic for game.xaml
    /// </summary>
    public partial class game : Page
    {
        public int ID;
        public game(int ID)
        {
            this.ID = ID;
            //get the connected players from the datavase

            InitializeComponent();
            Question();
        }


        public void Question()
        {

            MyStackPanel.Children.Clear(); // clears the answers from the last round.

            // get question from the server.

            this.question_lbl.Content = "quwestion";

            // get answers from the server.


            var answers = new string[4];



            ImageBrush imgBrush = new ImageBrush();
            imgBrush.ImageSource = new BitmapImage(new Uri("pack://application:,,,/images/answer.png"));
            for (int i = 0; i < 4; i++)
            {

                RadioButton rb = new RadioButton() { Content = answers[i], IsChecked = i == 0, Background = imgBrush, BorderBrush = null, Foreground = new SolidColorBrush(Colors.White), Template = (ControlTemplate)FindResource("ButtonBaseControlTemplate1") };

                rb.Checked += (sender, args) =>
                {

                    ImageBrush Brush = new ImageBrush();
                    Brush.ImageSource = new BitmapImage(new Uri("pack://application:,,,/images/answer_select.png"));
                    (sender as RadioButton).Background = Brush;

                    //the user selected the answer..
                    Console.WriteLine("Pressed " + (sender as RadioButton).Tag);

                };
                rb.Unchecked += (sender, args) => {
                    ImageBrush Brush = new ImageBrush();
                    Brush.ImageSource = new BitmapImage(new Uri("pack://application:,,,/images/answer.png"));
                    (sender as RadioButton).Background = Brush;
                };
                rb.Tag = i;


                MyStackPanel.Children.Add(rb);
            }
        }


    }
}
