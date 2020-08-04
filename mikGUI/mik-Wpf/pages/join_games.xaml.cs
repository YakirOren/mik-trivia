
using System;
using System.Collections.Generic;
using System.ComponentModel;
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

        private void InitializeBackgroundWorker()
        {
            parentWindow.backgroundWorker1.DoWork +=
                new DoWorkEventHandler(backgroundWorker1_DoWork);
            parentWindow.backgroundWorker1.RunWorkerCompleted +=
                new RunWorkerCompletedEventHandler(
            backgroundWorker1_RunWorkerCompleted);

            parentWindow.backgroundWorker1.ProgressChanged +=
                new ProgressChangedEventHandler(
            backgroundWorker1_ProgressChanged);
        }

        private void backgroundWorker1_ProgressChanged(object sender,
            ProgressChangedEventArgs e)
        {
            getGames();

        }

        private void backgroundWorker1_DoWork(object sender,
            DoWorkEventArgs e)
        {
            // Get the BackgroundWorker that raised this event.
            BackgroundWorker worker = sender as BackgroundWorker;

            // Assign the result of the computation
            // to the Result property of the DoWorkEventArgs
            // object. This is will be available to the 
            // RunWorkerCompleted eventhandler.

            int d = 0;
            while (!worker.CancellationPending)
            {
                d++;
                worker.ReportProgress(d);
                System.Threading.Thread.Sleep(5000);
                d = 0;
            }
            e.Cancel = true;



        }


        private void backgroundWorker1_RunWorkerCompleted(
            object sender, RunWorkerCompletedEventArgs e)
        {
            // First, handle the case where an exception was thrown.
            if (e.Error != null)
            {
                MessageBox.Show(e.Error.Message);
            }
            else if (e.Cancelled)
            {
                // Next, handle the case where the user canceled 
                // the operation.
                // Note that due to a race condition in 
                // the DoWork event handler, the Cancelled
                // flag may not have been set, even though
                // CancelAsync was called.
                System.Console.WriteLine("Canceled");
            }


        }




        public int CreateRoom()
        {
            int newRoomId = parentWindow.Client.CreateRoom(username);
            return newRoomId;
        }

        

        private void join_Click(object sender, RoutedEventArgs e)
        {
            parentWindow.backgroundWorker1.CancelAsync();
            int roomId = CreateRoom();
            create_texi dd = new create_texi(roomId, parentWindow.Client.getRoomState(roomId)[0], true);
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
                parentWindow.backgroundWorker1.WorkerReportsProgress = true;
                parentWindow.backgroundWorker1.WorkerSupportsCancellation = true;
                InitializeBackgroundWorker();

                username = parentWindow.username;
                player_name.Content = username;
                getGames();
            }

            parentWindow.backgroundWorker1.RunWorkerAsync(); // add active games. maybe add background thread for active games.

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
