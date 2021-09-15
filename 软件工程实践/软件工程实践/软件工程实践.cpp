#include<locale>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{

	locale china("zh_CN.UTF-8");//设置本地是中国，这样才能在文件中都入读出中文，而不乱码
	string words, orgs, answer;
	cin >> words; cin >> orgs; cin >> answer;
	wifstream infile2;
	infile2.open(orgs);
	infile2.imbue(china);//读入的是中文
	wstring a;
	int line = 0, total = 0; //line是储存第几行, total是敏感词个数
		ofstream outfile;//普通的文件输出
	outfile.open(answer);
	wofstream woutfile;//用来输出wstring
	woutfile.open(answer);
	woutfile.imbue(china);//输出中文
	woutfile << "Total:  " << endl;//准备用于被覆盖
	while (getline(infile2, a))//用来读入一行待检测文件
	{
		line++;
		for (unsigned int i = 0; i < a.size(); i++) {
			wifstream infile1;
			infile1.open(words);//用来打开敏感词
			infile1.imbue(china);//设置中国本地
			wstring b;//用来存放一行的敏感词
			while (getline(infile1, b))//读入一行敏感词
			{
				if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z'))//如果是英文；
				{
					unsigned int	k = 0, len = 0, count;
					while (k < b.size() && i + len < a.size())
					{
						if (b[k] == a[i + len] || b[k] == a[i + len] + 32 || b[k] == a[i + len] - 32)//英文字母不区分大小写相等 
							k++, len++, count = 0;//len是搜索到的敏感词的长度 ，count是敏感词之间符号的个数 
						else
						{
							if (a[i + len] >= 0 && a[i + len] <= 126
								&& !((a[i + len] >= 'a' && a[i + len] <= 'z') || (a[i + len] >= 'A' && a[i + len] <= 'Z')) && k != 0) //是敏感词中插入的字符 
								len++, count++;
							else break;
							if (count > 20) break;
						}
					}
					if (k == b.size()) {
						total++;//检测到的敏感词+1
						woutfile << "Line" << line << ": <";
						woutfile << b;
						woutfile << "> ";//输出："Line x:<敏感词>”
						for (unsigned int k = i; k < i + len; k++)
						{//输出待检测文档的敏感词
							woutfile << a[k];
						}
						woutfile << endl;
					}
				}
				else {
					unsigned int	k = 0, len = 0, count = 0;
					while (k < b.size() && i + len < a.size())
					{
						if (b[k] == a[i + len])
							k++, len++, count = 0;
						else
						{
							if (a[i + len] >= 0 && a[i + len] <= 126
								&& !((a[i + len] >= 'a' && a[i + len] <= 'z') || (a[i + len] >= 'A' && a[i + len] <= 'Z')) && k != 0)len++, count++;
							else break;
						}
						if (count > 20) break;
					}
					if (k == b.size()) {
						total++;//检测到的敏感词+1
						woutfile << "Line" << line << ": <";
						woutfile << b;
						woutfile << "> ";//输出："Line x:<敏感词>”
						for (unsigned int k = i; k < i + len; k++)
						{//输出待检测文档的敏感词
							woutfile << a[k];
						}
						woutfile << endl;
					}
				}
			}
		}
	}
	outfile << "Total:" << total;//输出检测出来的敏感词总数，会覆盖掉文件前面的空格
	outfile.close();//关闭文件
	woutfile.close();//关闭文件
	return 0;
}
/*d:words.txt d:org.txt d:answer.txt*/