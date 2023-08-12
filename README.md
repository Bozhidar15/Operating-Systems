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
tmux new -> command which open tmux sessing and your tutor can control your shell. to exit just write logout  
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
echo {text} -> will return exact what you have given after echo  
mkdir {name} -> create directory with the given name  
ls -> print all files(folders, files, links, sockets ...) in the current directory  
cd {path} -> enter/exit folder (cd .. -> exit current folder)  
touch {name} -> create file with specific given name ( if your use some kind of path this command create file without enter the directory)  
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

for example you have this path = /home/try/dog  
realpath {path} -> will return /home/try/dog  
basename {path} -> will return dog  
dirname {path} -> will return /home/try  

readlink {path} -> this will follow link  
df -> give free and used space of machine  

GLOBBING:  
? -> one random symbol  
* -> wildcard (>=0 random symbols)  

example: touch {bar, foo}_{q, p} -> this will create bar_q, bar_p, foo_q, foo_p  
find . -iname *.txt -> this will return all files ending on .txt no matter what is before it fmi.txt, car.txt, mouse.txt  

xargs -> gives you the power to combine 2 command one after another(do not use it)  
xxd {path} -> interprets the contents of the file by bytes  
paste {path1} {path2} -> combine two files in parallel
less {path} -> you can read content of a file using man page controls  
file {path} -> print information about given file  
cal -> calendar  
tar -c(create archive) -f(after this write the name of the archive) {name of the archive} {file1, file2, ....} -> create archive of files   
tar -x -f(after this write the name of the archive) {name of the archive} -> unzipped in current directory  
example: tar -cf project.tar project  
gzip {file} -> create compressed file.gz using DEFLATE algorithm  

PIPES AND STREAMS: 
{command1} > {file} -> result from command1 is saved to file(no need to be created in advance) 
> -> override
>> -> append to file

1> -> only stdout   
2> -> only stderr  
< -> stdin  

examples: 
{command} 2>&1 -> result from given command in stderr are redirected to stdout and they are mixed now  
{command} 2>&1 1> /dev/null -> stdout is redirected in /dev/null and stderr is redirected in stdout  
{command} 1>/dev/null 2>&1 -> stderr is redirected in stdout, which is already redirected in /dev/null so in conclution they both are redirected to /dev/null  
{command} 2>&3 1>&2 3>&1 -> changing stdout and stderr  

{command1} | {command2} -> stdout from command1 is stdin for command2 


wc {path} -> returning number of differant things like words, lines, sybols, bytes ec. in given path to file  
tr {Object1} {Object2} -> change object1 with object2(this command should take string from stdin)  
cut -> cutting table data  
sort -> lexicographic sorting  
du -> size of all files  
uniq -> take string and delete line if two adjacent rows are same.  
comm {file1} {file2} -> print 3 columns. The first column is the unique words from the first file. Second with the second file and third column with the same words.  
grep {string} {path} -> search and print only lines in which string match  
egrep == grep -e -> include regex (read regex(1))

REGEX:  
\t -> tab  
\n -> new line   
\r -> carrage return  

example:  
grep 'ba..' -> match string 'ba' and two randomm symbols  
anchors -> fixed positions:
- $ -> end of a line
- ^ -> star of line
- \> -> end of word
- \< -> start of word
- \b -> start and end of word

[...] -> symbol class (This means one random symbol)  
[^a-zA-Z] -> this means one random symbol without all small and big letters from a to z
\w -> if you use this in symbol class it means = a-zA-Z0-9  
[:alnum] [:alpha] [:digit] [:cntrl] [:lower] [:space] [:upper:] 

example:  
grep -e '[[:alpha:]_.]' -> symbol which is letter, underscore or dot
grep -e 'lift|elevator' -> catch lines with lift and with elevator (or)  
operator () > operator |  

ATOMS:  
{atom}* -> random number >=0  
{atom}+ -> random number >=1  
{atom}? -> random number 0 or 1  
{atom}{3,5} -> 3,4 or 5 times this atom  
{atom}{3,} -> 3 or infinity more times this atom  
{atom}{,42} -> max 42 times this atom  


how to escape ( or * in regex -> \( and \*  
sed -E -> regex use  
sed {string} -> like command tr but could use regex  
sed 's/quick/fast' -> s/ means change quick with fast one time in text  
sed 's/AA/BB/g' -> /g means for all matches  
sed could use differant separators  -> sed 's:AA:BB:g'  
