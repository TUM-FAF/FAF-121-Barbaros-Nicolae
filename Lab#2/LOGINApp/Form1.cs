using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Media;

namespace LOGINApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            SoundPlayer alersound = new SoundPlayer(@"D:\University\Anul2\Sem2\IDE\FormAps\LOGINApp\LOGINApp\Stranger.wav");

            //Play Sound On Click
            alersound.PlayLooping();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Getting the sound from the drive
            SoundPlayer simpleSound = new SoundPlayer(@"D:\University\Anul2\Sem2\IDE\FormAps\LOGINApp\LOGINApp\login.wav");

            //Play Sound On Click
            simpleSound.Play();

            //Connecting to dataBaseSql
            SqlConnection con = new SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=C:\Users\Nicolea\Documents\Data.mdf;Integrated Security=True;Connect Timeout=30");

            SqlDataAdapter sda = new SqlDataAdapter("Select Count(*) From Login where USERNAME='"+ textBox1.Text + "' and PASSWORD = '"+ textBox2.Text +"' ", con);

            //Getting Info from DataTable(@Username,Password)
            DataTable dt = new DataTable();
            sda.Fill(dt);
            if (dt.Rows[0][0].ToString() == "1")
            {
                //When press login a the loggin form will e hide out
                this.Hide();

                //new Main Objects
                Form2 ss = new Form2();

                //this will show the main form
                ss.Show();
            }

            else
            {
                MessageBox.Show("Please Check your Username and Password");
                SoundPlayer alersound = new SoundPlayer(@"D:\University\Anul2\Sem2\IDE\FormAps\LOGINApp\LOGINApp\Stranger.wav");

                //Play Sound On Click
                alersound.PlayLooping();
            }
           
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
