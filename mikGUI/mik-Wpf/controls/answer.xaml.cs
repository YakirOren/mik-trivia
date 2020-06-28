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
    /// Interaction logic for answer.xaml
    /// </summary>
    public partial class answer : UserControl
    {
        public bool state;
        public answer()
        {
            InitializeComponent();
        }

        private void answer_Click(object sender, RoutedEventArgs e)
        {
            state = !state;
            ImageBrush imgBrush = new ImageBrush();

            if (state)
            {
                imgBrush.ImageSource = new BitmapImage(new Uri("pack://application:,,,/images/answer_select.png"));

            }
            else
            {
                imgBrush.ImageSource = new BitmapImage(new Uri("pack://application:,,,/images/answer.png"));

            }

            answer_button.Background = imgBrush;


        }
    }
}
