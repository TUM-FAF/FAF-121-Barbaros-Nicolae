using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Media;
namespace LOGINApp
{
    public partial class Form2 : Form
    {
        int charIndex = 0;
        SoundPlayer alersound = new SoundPlayer(@"D:\University\Anul2\Sem2\IDE\FormAps\LOGINApp\LOGINApp\speak.wav");
        string text = "It is 4102. Aliens invaded us."
                       +"\nLuckily the world has some great engineers and you are one of them!"
                       + "\nYour'e working on an unbeatable weapon: Simulatron."
                       +"\nSimulatron is an exact copy of alien ship but it has a secret:"
                       +"\nwhen the alien gets into ship the alien is traped and he can't get out. "
                       + "\nYour task is very simple: you have to find them and destroy "
                       + "\n but be carefully, there is an evil who will try to hide tham well. "
                       +"\n\nWorld depends on you... Good luck"
                       +"\n\n\t\t Press Enter to continue";
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

           

            //Play Sound On Click
            alersound.Play();
            charIndex = 0;
            Thread s = new Thread(() => this.TyperWriterText(text));
            s.Start();
        }

        public void TyperWriterText(string _text)
        {
            while (charIndex < _text.Length)
            {
                Thread.Sleep(70);
                labelText.Invoke(new Action(() =>
                {
                    labelText.Text += _text[charIndex];
                }));
                charIndex++;

            }
        }


        //KeyDown Event (in my case is enter) this will open the last form
        private void KeyDown_(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                this.Hide();
                
                //if enter is pressed, audio is stoped
                alersound.Stop();
                //new Main Objects
                Main ss = new Main();
                
                //this will show the main form
                ss.Show();
            }
        }
    }
}
