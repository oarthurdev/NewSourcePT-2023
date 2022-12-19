using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Linq;
using Ionic.Zip;
using System.Net;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Net.Sockets;

namespace Launcher
{
    public partial class Form1 : Form
    {

        #region Inicialização de Variáveis

        System.Net.Sockets.TcpClient clientSocket = new System.Net.Sockets.TcpClient();
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;
        string Root = AppDomain.CurrentDomain.BaseDirectory;
        decimal versionlocal, versionserver;
        int timer = 8;

        #endregion

        #region Declarações de Funções Windows API

        [DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();

        #endregion

        #region Inicialização do Form

        public Form1()
        {
            InitializeComponent();
            lblLoading.Visible = false;
            bgwProcesso.RunWorkerAsync();
        }

        #endregion

        #region Botão Fechar
        private void btnClose_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void btnClose_MouseEnter(object sender, EventArgs e)
        {

            this.BackgroundImage = Properties.Resources.bg_2;
        }

        private void btnClose_MouseLeave(object sender, EventArgs e)
        {
            this.BackgroundImage = Properties.Resources.bg_1;
        }

        #endregion

        #region Função Janela Móvel

        private void Form1_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
        }

        #endregion

        #region Função Download and Install Update

        private void bgwProcesso_DoWork(object sender, DoWorkEventArgs e)
        {
            string Server = "http://54.39.78.116/VPS/";

            try
            {
                verifica();

                string lclVersion;

                using (StreamReader reader = new StreamReader(@Root + "\\game\\update\\version.dat"))
                {
                    lclVersion = reader.ReadLine();
                }

                decimal localVersion = decimal.Parse(lclVersion);

                versionlocal = localVersion;

                if (lblVerUpdate.InvokeRequired)
                {
                    lblVerUpdate.BeginInvoke
                    ((MethodInvoker)delegate
                    {
                        lblVerUpdate.Text = "     VERSION " + versionlocal;
                    });
                }

                XDocument serverXml = XDocument.Load(@Server + "Updates.xml");

                foreach (XElement update in serverXml.Descendants("update"))
                {
                    string version = update.Element("version").Value;

                    string file = update.Element("file").Value;

                    decimal serverVersion = decimal.Parse(version);

                    versionserver = serverVersion;

                    string sUrlToReadFileFrom = Server + file;

                    string sFilePathToWriteFileTo = Root + file;

                    if (serverVersion > localVersion)
                    {
                        if (lblStatus.InvokeRequired)
                        {
                            lblStatus.BeginInvoke
                            ((MethodInvoker)delegate
                            {
                                lblStatus.ForeColor = System.Drawing.Color.Orange;
                                lblStatus.Text = "                                UPDATING                                ";
                            });
                        }

                        Uri url = new Uri(sUrlToReadFileFrom);
                        System.Net.HttpWebRequest request = (System.Net.HttpWebRequest)System.Net.WebRequest.Create(url);
                        System.Net.HttpWebResponse response = (System.Net.HttpWebResponse)request.GetResponse();
                        response.Close();

                        Int64 iSize = response.ContentLength;

                        Int64 iRunningByteTotal = 0;

                        using (System.Net.WebClient client = new System.Net.WebClient())
                        {
                            using (System.IO.Stream streamRemote = client.OpenRead(new Uri(sUrlToReadFileFrom)))
                            {
                                using (Stream streamLocal = new FileStream(sFilePathToWriteFileTo, FileMode.Create, FileAccess.Write, FileShare.None))
                                {
                                    int iByteSize = 0;
                                    byte[] byteBuffer = new byte[iSize];
                                    while ((iByteSize = streamRemote.Read(byteBuffer, 0, byteBuffer.Length)) > 0)
                                    {
                                        streamLocal.Write(byteBuffer, 0, iByteSize);
                                        iRunningByteTotal += iByteSize;

                                        double dIndex = (double)(iRunningByteTotal);
                                        double dTotal = (double)byteBuffer.Length;
                                        double dProgressPercentage = (dIndex / dTotal);
                                        int iProgressPercentage = (int)(dProgressPercentage * 100);

                                        bgwProcesso.ReportProgress(iProgressPercentage);
                                    }
                                    streamLocal.Close();
                                }
                                streamRemote.Close();
                            }
                        }

                        using (ZipFile zip = ZipFile.Read(file))
                        {
                            foreach (ZipEntry zipFiles in zip)
                            {
                                zipFiles.Extract(@Root + "", true);
                            }
                        }

                        WebClient webClient = new WebClient();
                        webClient.DownloadFile(Server + "version.txt", @Root + "\\game\\update\\version.dat");
                        deleteFile(file);
                    }
                }
            }
            catch (Exception erro)
            {
                MessageBox.Show(erro.Message, "AVISO - Erro Encontrado!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Application.Exit();
            }
        }

        private void bgwProcesso_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            string vs = Convert.ToString(versionserver);

            string vl;

            if (versionserver == 1000)
            {
                vl = "0000";
            }
            else
            {
                vl = Convert.ToString(versionserver - 100);
            }

            lblVerUpdate.Text = vl + " -> " + vs + " " + e.ProgressPercentage + "%";
        }

        private void bgwProcesso_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            using (StreamReader reader = new StreamReader(@Root + "\\game\\update\\version.dat"))
            {
                string lclVersion = reader.ReadLine();
                decimal localVersion = decimal.Parse(lclVersion);
                lblVerUpdate.Text = "     VERSION " + Convert.ToString(localVersion);
            }
            status();
        }

        #endregion

        #region Função de Verificar Diretórios e Arquivos

        private void verifica()
        {
            try
            {
                string folder1 = @Root + "\\game\\update\\";


                if (!Directory.Exists(folder1))
                {
                    Directory.CreateDirectory(folder1);
                }

                FileStream fs1 = null;

                FileStream fs2 = null;

                FileStream fs3 = null;

                if (!File.Exists(@Root + "\\game\\update\\version.dat"))
                {
                    using (fs1 = File.Create(@Root + "\\game\\update\\version.dat"))
                    {

                    }

                    using (StreamWriter sw1 = new StreamWriter(@Root + "\\game\\update\\version.dat"))
                    {
                        sw1.Write("0000");
                    }
                }



                if (!File.Exists(@Root + "game.ini"))
                {
                    using (fs3 = File.Create(@Root + "game.ini"))
                    {

                    }

                    using (StreamWriter sw3 = new StreamWriter(@Root + "game.ini"))
                    {
                       //Macro 1
                        sw3.WriteLine("/camera_wave_off");
                        //Macro 2
                        sw3.WriteLine("/camera_wave_on");
                        //Macro 3
                       sw3.WriteLine("/disable_whisper");
                        //Macro 4
                       sw3.WriteLine("/enable_whisper");
                        //Macro 5
                        sw3.WriteLine("//party ");
                        //Macro 6
                        sw3.WriteLine("/TRADE ");
                        //Macro 7
                        sw3.WriteLine("/CLAN> ");
                        //Macro 8
                       sw3.WriteLine("/T> ");
                        //Macro 9
                        sw3.WriteLine("/V> ");
                        //Macro 10
                        sw3.WriteLine("/C> ");
                        //Opções Adicionais
                        sw3.WriteLine("# PristonTale+");
                        sw3.WriteLine("# config file");
                       sw3.WriteLine("");
                       sw3.WriteLine("[font]");
                        sw3.WriteLine("scaleX=0.01");
                       sw3.WriteLine("scaleY=0.01");
                       sw3.WriteLine("spacingAmount=0.0");
                        sw3.WriteLine("missingGlyph=32");
                       sw3.WriteLine("alpha=255");
                        sw3.WriteLine("");
                        sw3.WriteLine("[lang]");
                        sw3.WriteLine("fromcode=CP1252");
                        sw3.Write("transliteration=1");
                    }
                }
            }
            catch (Exception erro)
            {
                MessageBox.Show(erro.Message, "AVISO - Erro Encontrado!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Application.Exit();
            }
        }

        #endregion

        #region Função Deletar Arquivo após Update

        static bool deleteFile(string f)
        {
            try
            {
                File.Delete(f);
                return true;
            }
            catch (IOException)
            {
                return false;
            }
        }

        #endregion

        #region Função Status Server

        private void status()
        {
            try
            {
                clientSocket.Connect("54.39.78.116", 8000);

                if (clientSocket.Connected == true)
                {
                    lblStatus.ForeColor = System.Drawing.Color.GreenYellow;
                    lblStatus.Text = "                                 ONLINE                                 ";
                    tmLoading.Enabled = true;
                    lblLoading.Visible = true;
                }
                else
                {
                    lblStatus.ForeColor = System.Drawing.Color.OrangeRed;
                    lblStatus.Text = "                                MAINTENCE                               ";
                }

                clientSocket.Close();
            }
            catch (Exception)
            {
                lblStatus.ForeColor = System.Drawing.Color.Red;
                lblStatus.Text = "                                 OFFLINE                                ";
            }
        }

        #endregion

        #region Função Loading Game

        private void loading()
        {
            switch (timer)
            {
                case 7:
                    lblLoading.Text = "   LOADING GAME";
                    break;

                case 6:
                    lblLoading.Text = "  .LOADING GAME";
                    break;

                case 5:
                    lblLoading.Text = " ..LOADING GAME";
                    break;

                case 4:
                    lblLoading.Text = "...LOADING GAME";
                    break;

                case 3:
                    lblLoading.Text = "   LOADING GAME";
                    break;

                case 2:
                    lblLoading.Text = "  .LOADING GAME";
                    break;

                case 1:
                    lblLoading.Text = " ..LOADING GAME";
                    break;

                case 0:
                    lblLoading.Text = "...LOADING GAME";
                    break;

                default:
                    lblLoading.Text = "   LOADING GAME";
                    break;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void lblVerUpdate_Click(object sender, EventArgs e)
        {

        }

        private void lblStatus_Click(object sender, EventArgs e)
        {

        }

        private void lblLoading_Click(object sender, EventArgs e)
        {

        }

        private void tmLoading_Tick(object sender, EventArgs e)
        {
            if (timer >= 0)
            {
                timer = timer - 1;
                loading();
            }
            else
            {
                try
                {
                    Process.Start(@Root + "Game.exe", "Rubinho_FPT");
                    Application.Exit();
                }
                catch (Exception erro)
                {
                    MessageBox.Show(erro.Message, "AVISO - Erro Encontrado!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    Application.Exit();
                }
            }
        }

        #endregion

    }
}
