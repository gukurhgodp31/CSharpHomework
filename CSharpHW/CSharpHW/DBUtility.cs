using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;
using System.Data;

namespace CSharpHW
{
    class DBUtility
    {
        private static MySqlConnection conn;
        public void connect(String password, String dbName)
        {
            string connection = "server=localhost;user id=root;password="+password+";database="+dbName+"; pooling=true;";
            conn = new MySqlConnection(connection);
            conn.Open();
        }

        public void disconnect()
        {
            if (conn.State == ConnectionState.Open)
            {
                conn.Close();
            }
        }

        public static void getResultset(MySqlCommand mySqlCommand)
        {
            MySqlDataReader reader = mySqlCommand.ExecuteReader();
            try
            {
                while (reader.Read())
                {
                    if (reader.HasRows)
                    {
                        Console.WriteLine("编号:" + reader.GetInt32(0) + "|姓名:" + reader.GetString(1) + "|年龄:" + reader.GetInt32(2) + "|学历:" + reader.GetString(3));
                    }
                }
            }
            catch (Exception)
            {
                Console.WriteLine("查询失败了！");
            }
            finally
            {
                reader.Close();
            }
        }
        public static void insertIntoAccount(String category, int categoryNum, String inoutcome, int year, int month, int day, String amount, String RemarkText)
        {
            String sql = "INSERT INTO accounting.account VALUES(" + category + ", " + categoryNum + ", " + inoutcome + ", " + year + ", " + month + ", " + day + ", " + amount + ", " + RemarkText + ")";
            getExec(sql);
        }

        public static void createBudget(int budget)
        {
            String sql = "INSERT INTO accouting.budget VALUES(" + budget + ", 0)";
            getExec(sql);
        }

        public static void createPassword(int password)
        {
            String sql = "INSERT INTO accouting.password VALUES(" + password + ", 0)";
            getExec(sql);
        }

        public static void updateBudget(int budget)
        {
            //update student set name='李四' where id= 3
            String sql = "UPDATE accouting.budget SET budget=" + budget + " where id = 0";
            getExec(sql);
        }

        public static void updatePassword(int password)
        {
            //update student set name='李四' where id= 3
            String sql = "UPDATE accouting.password SET budget=" + password + " where id = 0";
            getExec(sql);
        }

        private static void getExec(String sql)
        {
            //"insert into account values(NULL,:category,:categoryNum,:inoutcome,:year,:month,:day,:amount,:remarktext)"
            //"INSERT INTO email.address (address) VALUES ('"+  address +"')"
            //"SELECT address FROM email.address WHERE id = " + id"
            MySqlCommand mySqlCommand = new MySqlCommand(sql, conn);
            try
            {
                mySqlCommand.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                String message = ex.Message;
                Console.WriteLine("插入数据失败了！" + message);
            }
        }
    }
}
