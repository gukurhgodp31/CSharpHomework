using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharpHW
{
    public partial class Accounting : Form
    {

        private static String InOutCome = "支出";
        private static int Year = 2016;
        private static int Month = 1;
        private static int Day = 1;
        public Accounting()
        {
            InitializeComponent();
        }

        private void button4_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {

            NormalBtn_Out.Visible = true;
            DietBtn_Out.Visible = true;
            TrafficBtn_Out.Visible = true;
            ClothesBtn_Out.Visible = true;
            MedicalBtn_Out.Visible = true;
            CommunicationBtn_Out.Visible = true;
            MakeupBtn_Out.Visible = true;
            StudyBtn_Out.Visible = true;
            ChemicalBtn_Out.Visible = true;
            EntertainmentBtn_Out.Visible = true;
            SocialBtn_Out.Visible = true;
            OtherBtn_Out.Visible = true;//显示类别中的支出项按钮

            NormalBtn_In.Visible = false;
            LivingExpenseBtn_In.Visible = false;
            BounsBtn_In.Visible = false;
            SalaryBtn_In.Visible = false;
            RedPacketBtn_In.Visible = false;
            OtherBtn_In.Visible = false;//隐藏类别中的收入项按钮


            InOutCome = "支出";
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void button9_Click(object sender, EventArgs e)
        {

        }

        private void IncomeBtn_Click(object sender, EventArgs e)
        {
            NormalBtn_Out.Visible             = false;
            DietBtn_Out.Visible               = false;
            TrafficBtn_Out.Visible            = false;
            ClothesBtn_Out.Visible            = false;
            MedicalBtn_Out.Visible            = false;
            CommunicationBtn_Out.Visible      = false;
            MakeupBtn_Out.Visible             = false;
            StudyBtn_Out.Visible              = false;
            ChemicalBtn_Out.Visible           = false;
            EntertainmentBtn_Out.Visible      = false;
            SocialBtn_Out.Visible             = false;
            OtherBtn_Out.Visible              = false;//隐藏类别中的支出项按钮

            NormalBtn_In.Visible              = true;
            LivingExpenseBtn_In.Visible       = true;
            BounsBtn_In.Visible               = true;
            SalaryBtn_In.Visible              = true;
            RedPacketBtn_In.Visible           = true;
            OtherBtn_In.Visible               = true;//显示类别中的收入项按钮


            InOutCome = "收入";
        }

        private void MedicalBtn_Out_Click(object sender, EventArgs e)
        {

        }
    }
}
