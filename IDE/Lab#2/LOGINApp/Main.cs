using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Media;
using System.IO;
using System.Text.RegularExpressions;
using System.Threading;
namespace LOGINApp
{
    public partial class Main : Form
    {
        int aliens;

        //this array of strings contains the keywords that will be searched
        string[] aliensList = new string[]{"aliens", "4102", "invaded", "utm", "help", "save", "faf121", "lab" };

        int charIndex = 0;

        string text = "Ready to Scan";
        string text2 = "No Aliens Found";
        string text3 = "Watch out!\nWe found them";
        public Main()
        {
            InitializeComponent();

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            //Getting the sound from the drive
            SoundPlayer simpleSound = new SoundPlayer(@"D:\University\Anul2\Sem2\IDE\FormAps\LOGINApp\LOGINApp\login.wav");

            //Play Sound On Click
            simpleSound.Play();

            folderBrowserDialog1.ShowDialog();
            lblfolder.Text = folderBrowserDialog1.SelectedPath;

            aliens = 0;

            lblaliens.Text = " " + aliens.ToString();

            //progress bar is zero
            progressBar1.Value = 0;

            //we reset everything before start
            listBox1.Items.Clear();

            //Start animating a Text
            charIndex = 0;
            lblTypeWriter.Text = string.Empty;

             //Getting the sound from the drive
            SoundPlayer scan = new SoundPlayer(@"D:\University\Anul2\Sem2\IDE\FormAps\LOGINApp\LOGINApp\scan.wav");

            //Play Sound On Click
            scan.Play();
            Thread t = new Thread(() => this.TyperWriterText(text));
            t.Start();

            
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            //Getting the sound from the drive
            SoundPlayer simpleSound = new SoundPlayer(@"D:\University\Anul2\Sem2\IDE\FormAps\LOGINApp\LOGINApp\login.wav");

            //Play Sound On Click
            simpleSound.Play();

            //serch for a specify folder
            List<string> search = Directory.GetFiles(@folderBrowserDialog1.SelectedPath, "*.*").ToList();

            //progress bar
            progressBar1.Maximum = search.Count;

            charIndex = 0;
            lblTypeWriter.Text = string.Empty;

                //array to search for intern files of this list
                foreach (string item in search)
                {
                    //try, catch for exceptions, sometimes we might get some exceptions
                    try
                    {
                        //
                        StreamReader stream = new StreamReader(item);

                        //read the hole file
                        string read = stream.ReadToEnd();

                        //after we get the file we need to go inside the file to search for words
                        foreach (string st in aliensList)
                        {
                            //if we get any match in the files with the aliens form aliensList
                            if (Regex.IsMatch(read, st))
                            {
                                aliens += 1;
                                lblaliens.Text = "Aliens: " + aliens.ToString();
                                listBox1.Items.Add(item);

                            }

                            progressBar1.Increment(1);

                        }
                    }

                    catch (Exception ex)
                    {

                    }
                }

                if (aliens == 0)
                {
                    SoundPlayer notfound = new SoundPlayer(@"D:\University\Anul2\Sem2\IDE\FormAps\LOGINApp\LOGINApp\notfound.wav");

                    //Play Sound On Click
                    notfound.Play();
                    Thread s = new Thread(() => this.TyperWriterText(text2));
                    s.Start();
                }

                else if (aliens > 0)
                {
                    SoundPlayer alersound = new SoundPlayer(@"D:\University\Anul2\Sem2\IDE\FormAps\LOGINApp\LOGINApp\alarm.wav");

                    //Play Sound On Click
                    alersound.PlayLooping();
                    Thread s = new Thread(() => this.TyperWriterText(text3));
                    s.Start();
                }
        }


        //TypeWriter function
        public void TyperWriterText(string _text)
        {
            while (charIndex < _text.Length)
            {
                Thread.Sleep(50);
                lblTypeWriter.Invoke(new Action(() =>
                    {
                        lblTypeWriter.Text += _text[charIndex ];
                    }));
                charIndex++ ;

            }
        }

        private void progressBar1_Click(object sender, EventArgs e)
        {

        }

        private void lblaliens_Click(object sender, EventArgs e)
        {

        }

        private void Main_Load(object sender, EventArgs e)
        {

        }

        private void lblTypeWriter_Click(object sender, EventArgs e)
        {

        }

        private void home_Click(object sender, EventArgs e)
        {
            //When press login a the loggin form will e hide out
            this.Hide();

            //new Main Objects
            Form1 ss = new Form1();

            //this will show the main form
            ss.Show();
        }
    }
}
