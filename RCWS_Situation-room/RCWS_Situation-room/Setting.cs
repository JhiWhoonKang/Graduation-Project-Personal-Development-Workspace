using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RCWS_Situation_room
{
    public partial class Setting : Form
    {
        public Setting()
        {
            InitializeComponent();
        }

        bool optical_menu_Expand = false;
        private void opticalTransition_Tick(object sender, EventArgs e)
        {
            if (optical_menu_Expand == false)
            {
                pnl_optical_setting_container.Height += 5;
                if (pnl_optical_setting_container.Height >= 180)
                {
                    opticalTransition.Stop();
                    optical_menu_Expand = true;
                }
            }
            else 
            {
                pnl_optical_setting_container.Height -= 5;
                if (pnl_optical_setting_container.Height <= 60)
                {
                    opticalTransition.Stop();
                    optical_menu_Expand = false;
                }
            }
        }

        private void btn_optical_setting_Click(object sender, EventArgs e)
        {
            opticalTransition.Start();
        }

        bool sidebarExpand = false;
        private void sidebarTransition_Tick(object sender, EventArgs e)
        {
            if (sidebarExpand)
            {
                sidebar.Width -= 5;
                if (sidebar.Width <= 52)
                {
                    sidebarExpand = false;
                    sidebarTransition.Stop();
                }
            }
            else
            {
                sidebar.Width += 5;
                if (sidebar.Width >= 149)
                {
                    sidebarExpand = true;
                    sidebarTransition.Stop();
                }
            }
        }

        private void btn_menu_Click(object sender, EventArgs e)
        {
            sidebarTransition.Start();
        }

        private void pb_close_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
