namespace RCWS_Situation_room
{
    partial class Setting
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
            this.components = new System.ComponentModel.Container();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.sidebar = new System.Windows.Forms.FlowLayoutPanel();
            this.pnl_optical_setting_container = new System.Windows.Forms.Panel();
            this.btn_reticle_setting = new System.Windows.Forms.Button();
            this.btn_optical_data_setting = new System.Windows.Forms.Button();
            this.btn_optical_setting = new System.Windows.Forms.Button();
            this.pnl_logout_container = new System.Windows.Forms.Panel();
            this.btn_logout = new System.Windows.Forms.Button();
            this.opticalTransition = new System.Windows.Forms.Timer(this.components);
            this.sidebarTransition = new System.Windows.Forms.Timer(this.components);
            this.panel2 = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.panel3 = new System.Windows.Forms.Panel();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.pictureBox5 = new System.Windows.Forms.PictureBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.pictureBox6 = new System.Windows.Forms.PictureBox();
            this.pb_close = new System.Windows.Forms.PictureBox();
            this.btn_menu = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.panel1.SuspendLayout();
            this.sidebar.SuspendLayout();
            this.pnl_optical_setting_container.SuspendLayout();
            this.pnl_logout_container.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox6)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_close)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.btn_menu)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.White;
            this.panel1.Controls.Add(this.pb_close);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.btn_menu);
            this.panel1.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1000, 50);
            this.panel1.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI Emoji", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(44, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(244, 26);
            this.label1.TabIndex = 2;
            this.label1.Text = "RCWS | CONFIGURATION";
            // 
            // sidebar
            // 
            this.sidebar.BackColor = System.Drawing.SystemColors.ControlDark;
            this.sidebar.Controls.Add(this.pnl_optical_setting_container);
            this.sidebar.Controls.Add(this.pnl_logout_container);
            this.sidebar.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.sidebar.Dock = System.Windows.Forms.DockStyle.Left;
            this.sidebar.Location = new System.Drawing.Point(0, 50);
            this.sidebar.Name = "sidebar";
            this.sidebar.Size = new System.Drawing.Size(52, 732);
            this.sidebar.TabIndex = 2;
            // 
            // pnl_optical_setting_container
            // 
            this.pnl_optical_setting_container.Controls.Add(this.pictureBox4);
            this.pnl_optical_setting_container.Controls.Add(this.pictureBox5);
            this.pnl_optical_setting_container.Controls.Add(this.pictureBox3);
            this.pnl_optical_setting_container.Controls.Add(this.btn_reticle_setting);
            this.pnl_optical_setting_container.Controls.Add(this.btn_optical_data_setting);
            this.pnl_optical_setting_container.Controls.Add(this.btn_optical_setting);
            this.pnl_optical_setting_container.Location = new System.Drawing.Point(0, 0);
            this.pnl_optical_setting_container.Margin = new System.Windows.Forms.Padding(0);
            this.pnl_optical_setting_container.Name = "pnl_optical_setting_container";
            this.pnl_optical_setting_container.Size = new System.Drawing.Size(149, 60);
            this.pnl_optical_setting_container.TabIndex = 5;
            // 
            // btn_reticle_setting
            // 
            this.btn_reticle_setting.BackColor = System.Drawing.SystemColors.ControlDark;
            this.btn_reticle_setting.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_reticle_setting.FlatAppearance.BorderSize = 0;
            this.btn_reticle_setting.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_reticle_setting.Font = new System.Drawing.Font("Segoe UI Emoji", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_reticle_setting.Location = new System.Drawing.Point(0, 120);
            this.btn_reticle_setting.Margin = new System.Windows.Forms.Padding(0);
            this.btn_reticle_setting.Name = "btn_reticle_setting";
            this.btn_reticle_setting.Size = new System.Drawing.Size(149, 60);
            this.btn_reticle_setting.TabIndex = 5;
            this.btn_reticle_setting.Text = "            Reticle";
            this.btn_reticle_setting.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btn_reticle_setting.UseVisualStyleBackColor = false;
            // 
            // btn_optical_data_setting
            // 
            this.btn_optical_data_setting.BackColor = System.Drawing.SystemColors.ControlDark;
            this.btn_optical_data_setting.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_optical_data_setting.FlatAppearance.BorderSize = 0;
            this.btn_optical_data_setting.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_optical_data_setting.Font = new System.Drawing.Font("Segoe UI Emoji", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_optical_data_setting.Location = new System.Drawing.Point(0, 60);
            this.btn_optical_data_setting.Margin = new System.Windows.Forms.Padding(0);
            this.btn_optical_data_setting.Name = "btn_optical_data_setting";
            this.btn_optical_data_setting.Size = new System.Drawing.Size(149, 60);
            this.btn_optical_data_setting.TabIndex = 6;
            this.btn_optical_data_setting.Text = "            Optical Data";
            this.btn_optical_data_setting.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btn_optical_data_setting.UseVisualStyleBackColor = false;
            // 
            // btn_optical_setting
            // 
            this.btn_optical_setting.BackColor = System.Drawing.SystemColors.ControlDark;
            this.btn_optical_setting.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_optical_setting.FlatAppearance.BorderSize = 0;
            this.btn_optical_setting.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_optical_setting.Font = new System.Drawing.Font("Segoe UI Emoji", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_optical_setting.ForeColor = System.Drawing.SystemColors.ControlText;
            this.btn_optical_setting.Location = new System.Drawing.Point(0, 0);
            this.btn_optical_setting.Margin = new System.Windows.Forms.Padding(0);
            this.btn_optical_setting.Name = "btn_optical_setting";
            this.btn_optical_setting.Size = new System.Drawing.Size(149, 60);
            this.btn_optical_setting.TabIndex = 4;
            this.btn_optical_setting.Text = "            Optical";
            this.btn_optical_setting.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btn_optical_setting.UseVisualStyleBackColor = false;
            this.btn_optical_setting.Click += new System.EventHandler(this.btn_optical_setting_Click);
            // 
            // pnl_logout_container
            // 
            this.pnl_logout_container.Controls.Add(this.pictureBox6);
            this.pnl_logout_container.Controls.Add(this.btn_logout);
            this.pnl_logout_container.Location = new System.Drawing.Point(0, 60);
            this.pnl_logout_container.Margin = new System.Windows.Forms.Padding(0);
            this.pnl_logout_container.Name = "pnl_logout_container";
            this.pnl_logout_container.Size = new System.Drawing.Size(149, 60);
            this.pnl_logout_container.TabIndex = 3;
            // 
            // btn_logout
            // 
            this.btn_logout.BackColor = System.Drawing.SystemColors.ControlDark;
            this.btn_logout.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_logout.FlatAppearance.BorderSize = 0;
            this.btn_logout.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_logout.Font = new System.Drawing.Font("Segoe UI Emoji", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_logout.ForeColor = System.Drawing.SystemColors.ControlText;
            this.btn_logout.Location = new System.Drawing.Point(0, 0);
            this.btn_logout.Margin = new System.Windows.Forms.Padding(0);
            this.btn_logout.Name = "btn_logout";
            this.btn_logout.Size = new System.Drawing.Size(149, 60);
            this.btn_logout.TabIndex = 5;
            this.btn_logout.Text = "            Logout";
            this.btn_logout.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btn_logout.UseVisualStyleBackColor = false;
            // 
            // opticalTransition
            // 
            this.opticalTransition.Interval = 10;
            this.opticalTransition.Tick += new System.EventHandler(this.opticalTransition_Tick);
            // 
            // sidebarTransition
            // 
            this.sidebarTransition.Interval = 10;
            this.sidebarTransition.Tick += new System.EventHandler(this.sidebarTransition_Tick);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.button1);
            this.panel2.Location = new System.Drawing.Point(104, 361);
            this.panel2.Margin = new System.Windows.Forms.Padding(0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(149, 60);
            this.panel2.TabIndex = 3;
            // 
            // button1
            // 
            this.button1.Dock = System.Windows.Forms.DockStyle.Top;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Location = new System.Drawing.Point(0, 0);
            this.button1.Margin = new System.Windows.Forms.Padding(0);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(149, 60);
            this.button1.TabIndex = 4;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Dock = System.Windows.Forms.DockStyle.Top;
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button2.Location = new System.Drawing.Point(0, 0);
            this.button2.Margin = new System.Windows.Forms.Padding(0);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(149, 60);
            this.button2.TabIndex = 5;
            this.button2.Text = "button2";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.button2);
            this.panel3.Location = new System.Drawing.Point(104, 443);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(149, 60);
            this.panel3.TabIndex = 10;
            // 
            // pictureBox4
            // 
            this.pictureBox4.BackColor = System.Drawing.SystemColors.ControlDark;
            this.pictureBox4.Image = global::RCWS_Situation_room.Properties.Resources.optical_icon;
            this.pictureBox4.Location = new System.Drawing.Point(10, 13);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(35, 35);
            this.pictureBox4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox4.TabIndex = 8;
            this.pictureBox4.TabStop = false;
            // 
            // pictureBox5
            // 
            this.pictureBox5.BackColor = System.Drawing.SystemColors.ControlDark;
            this.pictureBox5.Image = global::RCWS_Situation_room.Properties.Resources.database_icon;
            this.pictureBox5.Location = new System.Drawing.Point(10, 134);
            this.pictureBox5.Name = "pictureBox5";
            this.pictureBox5.Size = new System.Drawing.Size(35, 35);
            this.pictureBox5.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox5.TabIndex = 8;
            this.pictureBox5.TabStop = false;
            // 
            // pictureBox3
            // 
            this.pictureBox3.BackColor = System.Drawing.SystemColors.ControlDark;
            this.pictureBox3.Image = global::RCWS_Situation_room.Properties.Resources.reticle_icon;
            this.pictureBox3.Location = new System.Drawing.Point(10, 73);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(35, 35);
            this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox3.TabIndex = 8;
            this.pictureBox3.TabStop = false;
            // 
            // pictureBox6
            // 
            this.pictureBox6.BackColor = System.Drawing.SystemColors.ControlDark;
            this.pictureBox6.Image = global::RCWS_Situation_room.Properties.Resources.logout_icon;
            this.pictureBox6.Location = new System.Drawing.Point(10, 13);
            this.pictureBox6.Name = "pictureBox6";
            this.pictureBox6.Size = new System.Drawing.Size(35, 35);
            this.pictureBox6.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox6.TabIndex = 8;
            this.pictureBox6.TabStop = false;
            // 
            // pb_close
            // 
            this.pb_close.Image = global::RCWS_Situation_room.Properties.Resources.close_icon;
            this.pb_close.Location = new System.Drawing.Point(952, 7);
            this.pb_close.Name = "pb_close";
            this.pb_close.Size = new System.Drawing.Size(36, 36);
            this.pb_close.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pb_close.TabIndex = 2;
            this.pb_close.TabStop = false;
            this.pb_close.Click += new System.EventHandler(this.pb_close_Click);
            // 
            // btn_menu
            // 
            this.btn_menu.Image = global::RCWS_Situation_room.Properties.Resources.list_icon;
            this.btn_menu.Location = new System.Drawing.Point(12, 12);
            this.btn_menu.Name = "btn_menu";
            this.btn_menu.Size = new System.Drawing.Size(26, 26);
            this.btn_menu.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.btn_menu.TabIndex = 2;
            this.btn_menu.TabStop = false;
            this.btn_menu.Click += new System.EventHandler(this.btn_menu_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(104, 304);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(35, 35);
            this.pictureBox1.TabIndex = 12;
            this.pictureBox1.TabStop = false;
            // 
            // Setting
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(1000, 782);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.sidebar);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "Setting";
            this.Text = "Setting";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.sidebar.ResumeLayout(false);
            this.pnl_optical_setting_container.ResumeLayout(false);
            this.pnl_logout_container.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox6)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pb_close)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.btn_menu)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox btn_menu;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox pb_close;
        private System.Windows.Forms.FlowLayoutPanel sidebar;
        private System.Windows.Forms.Panel pnl_logout_container;
        private System.Windows.Forms.Button btn_optical_setting;
        private System.Windows.Forms.Panel pnl_optical_setting_container;
        private System.Windows.Forms.Button btn_logout;
        private System.Windows.Forms.Button btn_reticle_setting;
        private System.Windows.Forms.Button btn_optical_data_setting;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.PictureBox pictureBox5;
        private System.Windows.Forms.Timer opticalTransition;
        private System.Windows.Forms.PictureBox pictureBox6;
        private System.Windows.Forms.Timer sidebarTransition;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}