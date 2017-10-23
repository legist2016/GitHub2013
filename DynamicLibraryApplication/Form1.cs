using Microsoft.CSharp;
using System;
using System.CodeDom;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DynamicLibraryApplication
{
    public partial class Form1 : Form
    {
        string cspath = System.AppDomain.CurrentDomain.BaseDirectory + "DynamicClass";
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string ClassName = "NewEntityClass";
            string BaseName = "DynamicEntity";
            StringBuilder Codes = new StringBuilder();
            string CSFile = System.AppDomain.CurrentDomain.BaseDirectory + ClassName + ".cs";
            string template = Properties.Resources.StringPropertyTemplate;
            Codes.AppendFormat(template,  "Name", 20);
            Codes.AppendFormat(template, "Address", 120);
            Codes.AppendFormat(template, "Email", 50);
            Codes.AppendFormat(template, "Tel", 20);
            template = Properties.Resources.EntityTemplate;
            string content = string.Format(template, ClassName, BaseName, Codes);
            File.WriteAllText(CSFile ,content );

            CompilerResults result = DebugRun(
                new string[] {
                    cspath + ".cs",
                    CSFile,
                }
                , 
                cspath);
            foreach (CompilerError err in result.Errors)
            {
                Console.WriteLine("{0}({1},{2}): {5} {3}: {4}",err.FileName, err.Line, err.Column,err.ErrorNumber,err.ErrorText, err.IsWarning ?"warning":"error");
            }
            if (result.Errors.Count == 0)
                Console.WriteLine("{0} 编译成功", result.PathToAssembly);

        }

        /// <summary>
        /// 动态编译并执行代码
        /// </summary>
        /// <param name="code">代码</param>
        /// <returns>返回输出内容</returns>
        public CompilerResults DebugRun(string[] code, string newPath)
        {
            ICodeCompiler complier = new CSharpCodeProvider().CreateCompiler();
            
            //设置编译参数
            CompilerParameters paras = new CompilerParameters();
            //引入第三方dll
            
            paras.ReferencedAssemblies.Add("System.dll");
            paras.ReferencedAssemblies.Add("System.Core.dll");
            paras.ReferencedAssemblies.Add("DynamicEntityBaseLib.dll");
            paras.ReferencedAssemblies.Add("EntityFramework.dll");
            paras.ReferencedAssemblies.Add("System.ComponentModel.DataAnnotations.dll");
            //paras.ReferencedAssemblies.Add("System.dll");
            //引入自定义dll
            //paras.ReferencedAssemblies.Add(@"D:\自定义方法\自定义方法\bin\LogHelper.dll");
            //是否内存中生成输出 
            paras.GenerateInMemory = false;
            //是否生成可执行文件
            paras.GenerateExecutable = false;
            paras.OutputAssembly = newPath + ".dll";

            //编译代码
            //CompilerResults result = complier.CompileAssemblyFromFile(paras, code);
            //CompilerResults result = complier.CompileAssemblyFromSourceBatch(paras, code);
            CompilerResults result = complier.CompileAssemblyFromFileBatch(paras, code);

            return result;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Assembly assembly = Assembly.LoadFile(cspath+".dll");
            Type AType = assembly.GetType("DynamicLibraryApplication.DynamicClass");
            MethodInfo method = AType.GetMethod("DoWhat");
            var t = method.ReturnType.Name;
            object[] parameters = new object[] {  };
            var returnResult = Convert.ToString(method.Invoke(null, parameters));
        }
    }
}
