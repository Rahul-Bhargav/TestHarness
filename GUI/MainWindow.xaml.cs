///////////////////////////////////////////////////////////////////////
// MainWindow.xaml.cs - GUI for Project3HelpWPF                      //
// ver 1.0                                                           //
// Author : Lakshmi Harshini Kuchibhotla,                            //
//          CSE687 - Object Oriented Design, Spring 2018             //
// Source : Jim Fawcett, CSE687 - Object Oriented Design             //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package provides a WPF-based GUI for Project 4It's 
 * responsibilities are to:
 * - Provide a selection of test requests.
 * - It provides a view to see the selected dlls.
 * - you can modify the test name and the author
 * - you can see the test result files and run them.
 * - see the current status of the test request
 *   
 * Required Files:
 * ---------------
 * Mainwindow.xaml, MainWindow.xaml.cs
 * Translater.dll
 * 
 * Maintenance History:
 * --------------------
 * ver 1/1 : 07 Aug 2018
 * - fixed bug in DirList_MouseDoubleClick by returning when selectedDir is null
 * ver 1.0 : 30 Mar 2018
 * - first release
 * - Several early prototypes were discussed in class. Those are all superceded
 *   by this package.
 */

// Translater has to be statically linked with CommLibWrapper
// - loader can't find Translater.dll dependent CommLibWrapper.dll
using MsgPassingCommunication;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Forms;

namespace WpfApp1
{
    public class FileItem
    {
        public FileItem(String name, string relPath)
        {
            this.Name = name;
            FullPath = relPath;
        }
        public String Name { get; set; }
        public String FullPath { get; set; }
    }

    public class TestResult
    {
        public TestResult(String status, String logFile)
        {
            this.Status = status;
            this.LogFile = logFile;
        }
        public String Status { get; set; }
        public String LogFile { get; set; }
    }

    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        public String currentDirectory;
        public String CurrentDirectory { get { return currentDirectory; } set { currentDirectory = value; RaisePropertyChanged("CurrentDirectory"); } }

        public List<String> testRequestNames = new List<String>();

        public ObservableCollection<FileItem> DirectoryList { get; set; }

        public ObservableCollection<FileItem> SelectedList { get; set; }

        public ObservableCollection<String> TabsList { get; set; }

        public Dictionary<String, TestResult> ResultList { get; set; }

        public String currentStatus;
        public String CurrentStatus { get { return currentStatus; } set { currentStatus = value; RaisePropertyChanged("CurrentStatus"); } }

        public TestResult currentTestResult;

        public MainWindow()
        {
            InitializeComponent();
        }

        private Stack<string> pathStack_ = new Stack<string>();
        private Translater translater;
        private CsEndPoint endPoint_;
        private CsEndPoint serverEndPoint_;
        private Thread rcvThrd = null;
        private String sendFileDir_;

        //----< process incoming messages on child thread >----------------

        private void processMessages()
        {
            ThreadStart thrdProc = () =>
            {
                while (true)
                {
                    CsMessage msg = translater.getMessage();
                    if (msg.attributes.ContainsKey("log") && msg.attributes.ContainsKey("requestName"))
                    {
                        byte[] data = Convert.FromBase64String(msg.value("log"));
                        string decodedString = Encoding.UTF8.GetString(data);
                        string filePath = msg.value("requestName") + "-result" + ".txt";
                        decodedString = decodedString.Replace("\n", System.Environment.NewLine);
                        using (var streamWriter = File.CreateText(filePath))
                        {
                            streamWriter.Write(decodedString);

                        }
                        this.Dispatcher.Invoke(() =>
                        {
                            ResultList[msg.value("requestName")].Status += "\n\n Test request " + msg.value("requestName") + " executed \n\n " + "Find the result in -> " + filePath;
                            ResultList[msg.value("requestName")].LogFile = filePath;
                            UpdateCurrentStatus();
                            string[] args = Environment.GetCommandLineArgs();
                            if (args.Length > 1 && args[1] == "INDEMO")
                                Process.Start(filePath);

                        });
                    }
                }
            };
            rcvThrd = new Thread(thrdProc);
            rcvThrd.IsBackground = true;
            rcvThrd.Start();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            CurrentDirectory = System.IO.Directory.GetCurrentDirectory();

            // start Comm
            endPoint_ = new CsEndPoint();
            endPoint_.machineAddress = "localhost";
            endPoint_.port = 8086;
            translater = new Translater();
            translater.listen(endPoint_);

            serverEndPoint_ = new CsEndPoint();
            serverEndPoint_.machineAddress = "localhost";
            serverEndPoint_.port = 8081;

            // start processing messages
            processMessages();

            sendFileDir_ = CurrentDirectory + "\\SendFiles";
            Directory.CreateDirectory(sendFileDir_);
            translater.SetSendFileDirectory(sendFileDir_);
            //test1();
            DirectoryList = new ObservableCollection<FileItem>();
            SelectedList = new ObservableCollection<FileItem>();
            TabsList = new ObservableCollection<String>();
            ResultList = new Dictionary<string, TestResult>();
            UpdateDirectoryFiles();
            DirectoryListBox.ItemsSource = DirectoryList;
            SelectedFilesListBox.ItemsSource = SelectedList;
            string[] args = Environment.GetCommandLineArgs();
            ResultGrid.Visibility = Visibility.Collapsed;
            if (args.Length > 1 && args[1] == "INDEMO")
                StartDemo();
        }

        async Task PutTaskDelay(int delay)
        {
            await Task.Delay(delay);
        }

        private async void StartDemo()
        {
            await PutTaskDelay(2000);
            CurrentDirectory = System.IO.Directory.GetParent(CurrentDirectory).FullName + "\\Debug";
            UpdateDirectoryFiles();
            await PutTaskDelay(2000);
            DirectoryListBox.SelectedIndex = 1;
            await PutTaskDelay(2000);
            typeof(System.Windows.Controls.Primitives.ButtonBase).GetMethod("OnClick", BindingFlags.Instance | BindingFlags.NonPublic).Invoke(SelectFile, new object[0]);
            await PutTaskDelay(2000);
            DirectoryListBox.SelectedIndex = 0;
            await PutTaskDelay(2000);
            typeof(System.Windows.Controls.Primitives.ButtonBase).GetMethod("OnClick", BindingFlags.Instance | BindingFlags.NonPublic).Invoke(SelectFile, new object[0]);
            await PutTaskDelay(2000);
            TestNameTextBox.Text = "Time Taking Test";
            await PutTaskDelay(2000);
            AuthorTextBox.Text = "Rahul";
            await PutTaskDelay(2000);
            typeof(System.Windows.Controls.Primitives.ButtonBase).GetMethod("OnClick", BindingFlags.Instance | BindingFlags.NonPublic).Invoke(SendTest, new object[0]);



            DirectoryListBox.SelectedIndex = 2;
            await PutTaskDelay(2000);
            typeof(System.Windows.Controls.Primitives.ButtonBase).GetMethod("OnClick", BindingFlags.Instance | BindingFlags.NonPublic).Invoke(SelectFile, new object[0]);
            await PutTaskDelay(2000);
            TestNameTextBox.Text = "Demo Req";
            await PutTaskDelay(2000);
            AuthorTextBox.Text = "Rahul";
            await PutTaskDelay(2000);
            typeof(System.Windows.Controls.Primitives.ButtonBase).GetMethod("OnClick", BindingFlags.Instance | BindingFlags.NonPublic).Invoke(SendTest, new object[0]);
            await PutTaskDelay(5000);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        public void SelectFile_Click(object sender, EventArgs e)
        {

            //List<FileItem> tempList = new List<FileItem>(DirectoryListBox.SelectedItems.Count);
            foreach (FileItem item in DirectoryListBox.SelectedItems)
            {
                bool isExisting = false;
                foreach (var selectedFileItem in SelectedList)
                {
                    if (selectedFileItem.Name == item.Name)
                        isExisting = true;
                }
                if (isExisting)
                {
                    System.Windows.Forms.MessageBox.Show("File with same name already exists, please try another file");
                    return;
                }
                SelectedList.Add(item);
            }
            SelectedFilesListBox.ItemsSource = SelectedList;
            DirectoryListBox.SelectedIndex = -1;
        }


        public void DeSelectFile_Click(object sender, EventArgs e)
        {
            List<FileItem> temp = new List<FileItem>();
            foreach (FileItem item in SelectedList)
            {
                temp.Add(item);
            }
            foreach (FileItem item in SelectedFilesListBox.SelectedItems)
            {
                temp.Remove(item);
            }
            SelectedList.Clear();
            temp.ForEach((item) => { SelectedList.Add(item); });
        }

        private void SendTestFiles(List<String> dllFiles)
        {
            foreach (var item in dllFiles)
            {
                CsMessage message = new CsMessage();
                message.add("to", CsEndPoint.toString(serverEndPoint_));
                message.add("from", CsEndPoint.toString(endPoint_));
                message.add("sendingFile", item);
                message.add("name", "DLL File - " + item);
                translater.postMessage(message);
            }
        }

        private void PostTestRequest(String Name, String Author, List<String> dllFiles)
        {

            SendTestFiles(dllFiles);

            CsMessage message = translater.GetTestRequestMessage(Author, Name, dllFiles);
            message.add("to", CsEndPoint.toString(serverEndPoint_));
            message.add("from", CsEndPoint.toString(endPoint_));
            translater.postMessage(message);

        }

        private void SelectDirectory_Click(object sender, RoutedEventArgs e)
        {
            using (var fbd = new FolderBrowserDialog())
            {
                fbd.SelectedPath = CurrentDirectory;
                System.Windows.Forms.DialogResult result = fbd.ShowDialog();

                if (result == System.Windows.Forms.DialogResult.OK && !string.IsNullOrWhiteSpace(fbd.SelectedPath))
                {
                    CurrentDirectory = fbd.SelectedPath;

                    UpdateDirectoryFiles();
                }
            }
        }

        private void UpdateDirectoryFiles()
        {
            string[] files = System.IO.Directory.GetFiles(this.CurrentDirectory);
            DirectoryList.Clear();
            foreach (string fullFile in files)
            {
                string[] split = fullFile.Split('\\');
                string file = split[split.Length - 1];
                string ext = Path.GetExtension(file);
                if (ext.ToLower() == ".dll")
                {
                    DirectoryList.Add(new FileItem(file, this.CurrentDirectory + "\\" + file));
                }
            }
        }

        private void GetFilesToSendingDirectory()
        {
            foreach (var file in SelectedList)
            {
                File.Copy(file.FullPath, sendFileDir_ + "\\" + file.Name, true);
            }
        }

        private void SendTest_Click(object sender, RoutedEventArgs e)
        {
            ResultPlaceHolder.Visibility = Visibility.Collapsed;
            ResultGrid.Visibility = Visibility.Visible;
            String Author = AuthorTextBox.Text.Trim(' ');
            String Name = TestNameTextBox.Text.Trim(' ');
            if (SelectedList.Count < 1 || Author == "" || Name == "")
            {
                System.Windows.Forms.MessageBox.Show("Please make sure you have filled all the details");
                return;
            }
            if (testRequestNames.Contains(Name))
            {
                System.Windows.Forms.MessageBox.Show("A Request with the same name is already executed, please choose a unique name.");
                return;
            }
            TabItem tabItem = new TabItem();
            tabItem.Header = Name;
            TestResult testResult = new TestResult("","");

            ResultList.Add(Name, testResult);
            ResultsTabControl.Items.Add(tabItem);
            ResultsTabControl.SelectedItem = tabItem;
            testResult.Status = "\n\nProcessing\n\n";
            currentTestResult = testResult;
            CurrentStatus = currentTestResult.Status;
            GetFilesToSendingDirectory();

            List<String> dlls = new List<string>();
            foreach (var item in SelectedList)
            {
                dlls.Add(item.Name);
            }
            PostTestRequest(Name, Author, dlls);
            SelectedList.Clear();
            testRequestNames.Add(Name);
        }

        private void ResultsTabControl_TabChanged(object sender, SelectionChangedEventArgs e)
        {
            TabItem selected = ResultsTabControl.SelectedItem as TabItem;
            currentTestResult = ResultList[selected.Header as String];
            CurrentStatus = currentTestResult.Status;
        }

        private void UpdateCurrentStatus()
        {
            CurrentStatus = currentTestResult.Status;
        }

        private void OpenLog_Click(object sender, RoutedEventArgs e)
        {
            if (currentTestResult != null)
                Process.Start(currentTestResult.LogFile);
        }
    }
}
