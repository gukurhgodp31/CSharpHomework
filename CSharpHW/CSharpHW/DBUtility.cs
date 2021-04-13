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
        private MySqlConnection conn;
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

        public static MySqlCommand getSqlCommand(String sql, MySqlConnection mysql)
        {
            MySqlCommand mySqlCommand = new MySqlCommand(sql, mysql);
            return mySqlCommand;
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

        public static void getInsert(MySqlCommand mySqlCommand)
        {
            //"insert into account values(NULL,:category,:categoryNum,:inoutcome,:year,:month,:day,:amount,:remarktext)"
            //"INSERT INTO email.address (address) VALUES ('"+  address +"')"
            //"SELECT address FROM email.address WHERE id = " + id
            String insert = "INSERT";
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
