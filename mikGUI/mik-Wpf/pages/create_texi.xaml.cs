using System.ComponentModel;
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
        private System.ComponentModel.BackgroundWorker backgroundWorker1 = new BackgroundWorker();

        public create_texi(int gameID, string AdminName, bool isAdmin = false)
        {
            this.gameID = gameID;
            this.isAdmin = isAdmin;
            this.AdminName = AdminName;
            backgroundWorker1.WorkerReportsProgress = true;
            backgroundWorker1.WorkerSupportsCancellation = true;

            InitializeComponent();
            InitializeBackgroundWorker();

            if (!this.isAdmin)
            {
                this.submit.Visibility = Visibility.Hidden;
            }

        }


        // Set up the BackgroundWorker object by 
        // attaching event handlers. 
        private void InitializeBackgroundWorker()
        {
            backgroundWorker1.DoWork +=
                new DoWorkEventHandler(backgroundWorker1_DoWork);
            backgroundWorker1.RunWorkerCompleted +=
                new RunWorkerCompletedEventHandler(
            backgroundWorker1_RunWorkerCompleted);

            backgroundWorker1.ProgressChanged +=
                new ProgressChangedEventHandler(
            backgroundWorker1_ProgressChanged);
        }


        private void backgroundWorker1_ProgressChanged(object sender,
            ProgressChangedEventArgs e)
        {
            players.Children.Clear();

            var d = mainWindow.Client.getRoomState(this.gameID);

            driver_lbl.Text = d[0];

            d.RemoveAt(0);

            foreach (var name in d)
            {
                var new_game = new lobby_user(name);
                players.Children.Add(new_game);
                System.Console.WriteLine(name);

            }

        }


        // This event handler is where the actual,
        // potentially time-consuming work is done.
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
                System.Threading.Thread.Sleep(3000);
                d = 0;
            }
            e.Cancel = true;



        }

        // This event handler deals with the results of the
        // background operation.
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



        private void Window_Loaded(object sender, RoutedEventArgs e)
        {

            mainWindow = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();

            if (mainWindow != null)
            {
                driver_lbl.Text = mainWindow.username;
            }


            //get list of connected users from the data base.

            // when a new player joins add him to the list.


            // Start the asynchronous operation.
            backgroundWorker1.RunWorkerAsync();

            //getPlayers();

            //mainWindow.Client.socket.ReceiveAll(); // wait for a messge from the server (the messge will be that a new client has join the room and this client should update the )




        }


        public void getPlayers()
        {
            players.Children.Clear();

            var d = mainWindow.Client.getRoomState(this.gameID);

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

            mainWindow.Client.startGameRequest(this.gameID);
            backgroundWorker1.CancelAsync();
            _gameFrame.Navigate(new game(gameID));


        }

        private void Window_Closing(object sender, CancelEventArgs e)
        {
            if (isAdmin)
            {
                mainWindow.Client.closeRoom(this.gameID);
            }
            else
            {
                mainWindow.Client.leaveRoom(this.gameID);
            }

            backgroundWorker1.CancelAsync();

            mainWindow.backgroundWorker1.RunWorkerAsync();
            //this.Close();
        }
    }
}
