#include <stdio.h>
#include <python3.6m/Python.h>

// 加载rpc服务端的脚本
int start_rpc_server(void)
{
	Py_Initialize();
	PyRun_SimpleString("print('Hello World!')");
	Py_Finalize();

	return 0;
}

int main(int argc, char **argv)
{
	start_rpc_server();
	return 0;
}
