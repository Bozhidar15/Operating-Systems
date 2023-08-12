# Operating Systems
## task and solutions
- [02.commands](https://github.com/Bozhidar15/Operating-Systems/tree/main/02.commands)  
- [03.pipes](https://github.com/Bozhidar15/Operating-Systems/tree/main/03.pipes)
- [04.process](https://github.com/Bozhidar15/Operating-Systems/tree/main/04.processes)
- [05.scripts](https://github.com/Bozhidar15/Operating-Systems/tree/main/05.scripts)
  
###### Решените задачи от следващите 2 раздела са от файла os-problems.pdf (първото число представлява номера на задачата; второто годината, когато е дадена тази задача; третото на коя специалност; четвъртото колко пъти се е падала тази задача през годините; Да се обърне внимание, че файла os-problems.pdf е бил променян и първото число няма да съответва на задачата, затова да се гледат следващите 3 )
- [collection of shell](https://github.com/Bozhidar15/Operating-Systems/tree/main/CollectionOfShell)
- [collection of C](https://github.com/Bozhidar15/Operating-Systems/tree/main/CollectionOfC)

### general knowledge
relative path -> path from one folder(not root) to the bottom  
absolute path -> path starting from root to the bottom  
. -> current directory (you can use this in commands)  
~ -> your home directory (you can use this in commands)  
shell -> sh, csh, ksh, bash, dash  
/tmp -> temporary directory in which all users (accounts) can share files  
/etc/passwd -> file which show all accounts  
sudo -> key command; DO NOT USE IF YOU DONT HAVE RIGHTS; give administration power  
sudo {command} -> run current command from root  
sudo -u {user} {command} -> run command from given user  
Every command could user flags ( -r -s -f ....) in man page of a command you can find which flag do you need 
#### shell commands (you can pass relative and absolute paths to the commands)  
man {command} -> open information page of current entered command  
pwd -> show current directory where I am  
whoami -> return your username  
mkdir {name} -> create directory with the given name  
ls -> print all files(folders, files, links, sockets ...) in the current directory  
cd {path} -> enter/exit folder (cd .. -> exit current folder)  
touch {name} -> create file with specific given name ( if your use some kind of path this command create file without enter the directory  
mv {path1} {path2} -> move file from path1 to path2 (this command is alsome used for rename a file, just past the same path but with new name at the end)  
cp {path1} {dir} -> copy file from path to dir   
rm {path} -> remove file from given path  
rmdir {path} -> delete empty directory  
cat {path to file} -> print file content  
head {path} -> print first 10 rows of given file  
tail {path} -> print last 10 rows of given file  
stat {path} -> show status or wanted features of a given file  
chown {path} -> change owner of a file  
find {path} (flags) -> powerful command, which you can use to find information about features of a directory or files  
ln {new path} {old path} -> create link/pointer from one file  
