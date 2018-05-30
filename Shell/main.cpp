#include"Shell.h"
void main() {
	Shell shell(TEXT("C:\\Windows\\System32\\cmd.exe"));
	string out;
	string inp;
	out.resize(500);
	inp.resize(100);
	Sleep(1000);
	while (true) {
		shell.GetOutput(">", 10000, out);

		cout << out.substr(out.find('\n'));
		getline(cin, inp);
		if (!shell.SetInput(inp)) {
			cout << "Set Failed!" << endl;
			break;
		}
	}
}