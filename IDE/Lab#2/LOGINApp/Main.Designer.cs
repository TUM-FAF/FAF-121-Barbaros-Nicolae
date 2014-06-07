namespace LOGINApp
{
    partial class Main
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.brows = new System.Windows.Forms.Button();
            this.lblfolder = new System.Windows.Forms.Label();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.lblaliens = new System.Windows.Forms.Label();
            this.lblTypeWriter = new System.Windows.Forms.Label();
            this.home = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // progressBar1
            // 
            this.progressBar1.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.progressBar1.BackColor = System.Drawing.Color.LightBlue;
            this.progressBar1.Cursor = System.Windows.Forms.Cursors.PanNW;
            this.progressBar1.ForeColor = System.Drawing.Color.LightBlue;
            this.progressBar1.Location = new System.Drawing.Point(57, 275);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(541, 23);
            this.progressBar1.Step = 1;
            this.progressBar1.TabIndex = 1;
            this.progressBar1.Click += new System.EventHandler(this.progressBar1_Click);
            // 
            // listBox1
            // 
            this.listBox1.BackColor = System.Drawing.Color.SteelBlue;
            this.listBox1.FormattingEnabled = true;
            this.listBox1.HorizontalScrollbar = true;
            this.listBox1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.listBox1.Location = new System.Drawing.Point(221, 104);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(231, 108);
            this.listBox1.TabIndex = 2;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.Transparent;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.ForeColor = System.Drawing.Color.SteelBlue;
            this.button1.Location = new System.Drawing.Point(346, 218);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(106, 51);
            this.button1.TabIndex = 4;
            this.button1.Text = "Scan";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // brows
            // 
            this.brows.BackColor = System.Drawing.Color.Transparent;
            this.brows.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.brows.ForeColor = System.Drawing.Color.SteelBlue;
            this.brows.Location = new System.Drawing.Point(221, 218);
            this.brows.Name = "brows";
            this.brows.Size = new System.Drawing.Size(119, 51);
            this.brows.TabIndex = 5;
            this.brows.Text = "Browse";
            this.brows.UseVisualStyleBackColor = false;
            this.brows.Click += new System.EventHandler(this.button2_Click);
            // 
            // lblfolder
            // 
            this.lblfolder.AutoSize = true;
            this.lblfolder.BackColor = System.Drawing.Color.Transparent;
            this.lblfolder.Font = new System.Drawing.Font("VAIO CON DIOS", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblfolder.ForeColor = System.Drawing.Color.AliceBlue;
            this.lblfolder.Location = new System.Drawing.Point(53, 68);
            this.lblfolder.Name = "lblfolder";
            this.lblfolder.Size = new System.Drawing.Size(0, 22);
            this.lblfolder.TabIndex = 6;
            this.lblfolder.Click += new System.EventHandler(this.label1_Click);
            // 
            // lblaliens
            // 
            this.lblaliens.AutoSize = true;
            this.lblaliens.BackColor = System.Drawing.Color.Transparent;
            this.lblaliens.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblaliens.ForeColor = System.Drawing.Color.LightBlue;
            this.lblaliens.Location = new System.Drawing.Point(458, 192);
            this.lblaliens.Name = "lblaliens";
            this.lblaliens.Size = new System.Drawing.Size(0, 20);
            this.lblaliens.TabIndex = 7;
            this.lblaliens.Click += new System.EventHandler(this.lblaliens_Click);
            // 
            // lblTypeWriter
            // 
            this.lblTypeWriter.AutoSize = true;
            this.lblTypeWriter.BackColor = System.Drawing.Color.Transparent;
            this.lblTypeWriter.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTypeWriter.ForeColor = System.Drawing.Color.LightBlue;
            this.lblTypeWriter.Location = new System.Drawing.Point(458, 104);
            this.lblTypeWriter.Name = "lblTypeWriter";
            this.lblTypeWriter.Size = new System.Drawing.Size(0, 20);
            this.lblTypeWriter.TabIndex = 8;
            this.lblTypeWriter.Click += new System.EventHandler(this.lblTypeWriter_Click);
            // 
            // home
            // 
            this.home.BackColor = System.Drawing.Color.Transparent;
            this.home.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.home.ForeColor = System.Drawing.Color.SteelBlue;
            this.home.Location = new System.Drawing.Point(2, 339);
            this.home.Name = "home";
            this.home.Size = new System.Drawing.Size(51, 26);
            this.home.TabIndex = 9;
            this.home.Text = "Back";
            this.home.UseVisualStyleBackColor = false;
            this.home.Click += new System.EventHandler(this.home_Click);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(624, 361);
            this.Controls.Add(this.home);
            this.Controls.Add(this.lblTypeWriter);
            this.Controls.Add(this.lblaliens);
            this.Controls.Add(this.lblfolder);
            this.Controls.Add(this.brows);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.progressBar1);
            this.Cursor = System.Windows.Forms.Cursors.PanNW;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Simulatron - Find the enemy";
            this.Load += new System.EventHandler(this.Main_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button brows;
        private System.Windows.Forms.Label lblfolder;
        public System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Label lblaliens;
        private System.Windows.Forms.Label lblTypeWriter;
        private System.Windows.Forms.Button home;

    }
}