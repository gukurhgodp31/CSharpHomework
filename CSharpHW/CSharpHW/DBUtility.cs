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
    }
}
