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
    public partial class FormDataSetting : Form
    {
        public FormDataSetting()
        {
            InitializeComponent();
        }

        private void FormDataSetting_Load(object sender, EventArgs e)
        {
            this.ControlBox = false;
        }

        public void DisplayReceivedData(string data)
        {
            rtb_receivetcp.Invoke((MethodInvoker)delegate {
                rtb_receivetcp.AppendText(data + "\r\n");
                rtb_receivetcp.ScrollToCaret();
            });
        }

        private void SendTcp(string str)
        {
            rtb_sendtcp.Invoke((MethodInvoker)delegate { rtb_sendtcp.AppendText(str + "\r\n"); });
            rtb_sendtcp.Invoke((MethodInvoker)delegate { rtb_sendtcp.ScrollToCaret(); });
        }

        private void ReceiveTcp(string str)
        {
            rtb_receivetcp.Invoke((MethodInvoker)delegate { rtb_receivetcp.AppendText(str + "\r\n"); });
            rtb_receivetcp.Invoke((MethodInvoker)delegate { rtb_receivetcp.ScrollToCaret(); });
        }
    }
}