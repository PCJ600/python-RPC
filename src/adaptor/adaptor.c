#include <stdio.h>
#include <python3.6m/Python.h>

#define OK 0
#define ERR (-1)
#define LOG_FILE "/opt/diag.log"			// TODO: 判断路径不存在
#define PY_MODULE_PATH "/usr/local/bin/RPC" // TODO: 判断路径不存在
#define BUFFER_SIZE 256

// 记录诊断日志到LOG_FILE
void WriteLog(const char *fmt, ...) 
{
	FILE *fp = fopen(LOG_FILE, "a+");
	if(fp == NULL) {
		return;	
	}
		
	va_list ap;
	va_start(ap, fmt);
	vfprintf(fp, fmt, ap);
	va_end(ap);
	fclose(fp);
}


// C进程里加载server.py, 开启RPC服务端
int start_rpc_server(void)
{
	Py_Initialize();
	if(!Py_IsInitialized()) {
		WriteLog("[ERROR]: Python Init failed!\n");
		return ERR;
	}

	// 指定加载的Python模块的具体路径
	char pyStr[BUFFER_SIZE];
	PyRun_SimpleString("import sys");
	sprintf(pyStr, "sys.path.append('%s')", PY_MODULE_PATH);
	PyRun_SimpleString(pyStr);

	// 导入rpc服务端模块，模块名为server
	PyObject *pyModule = PyImport_ImportModule("server");
	if(pyModule == NULL) {
		WriteLog("[ERROR]: import server.py failed!\n");
		return ERR;
	}

	// 获取py模块字典，并调用其中start_rpc_server方法打开服务端
	PyObject *pyDict = PyModule_GetDict(pyModule);
	if(pyDict == NULL) {
		WriteLog("[ERROR]: can't find dict in server.py!\n");
		return ERR;
	}

	// 获取server模块中start_rpc_server函数，开启rpc服务端
	const char *funcName = "start_rpc_server";
	PyObject *pyFunc = PyDict_GetItemString(pyDict, funcName);
	if(!pyFunc || !PyCallable_Check(pyFunc)) {
		WriteLog("[ERROR]: can't find func %s in server.py!\n", funcName);
		return ERR;
	}
	PyObject_CallObject(pyFunc, NULL); // 如调用正常，服务端开启成功，并等待客户端请求

	Py_Finalize();

	return OK;
}

int main(int argc, char **argv)
{
	start_rpc_server();
	return 0;
}









