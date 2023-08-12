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
init -> program which start right after starting our operating system  
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
chsh -> changing shell by default  
alias {name}={command} -> creating your own command (alias home_usage="df -h ~ | awk 'NR>1{print $5}'" )  
unalias {name} -> delete command  
add command permanently: add your code to this file : ~/.bash_profile || ~/.profile || ~/.bashrc || /etc/bashrc  


### shell commands (you can pass relative and absolute paths to the commands)  
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
chmod -> change file/directory access rights settings  
find {path} (flags) -> powerful command, which you can use to find information about features of a directory or files  
ln {new path} {old path} -> create link/pointer from one file  

for example you have this path = /home/try/dog  
realpath {path} -> will return /home/try/dog  
basename {path} -> will return dog  
dirname {path} -> will return /home/try  

readlink {path} -> this will follow link  
df -> give free and used space of machine  

GLOBBING:  
'?' -> one random symbol  
'*' -> wildcard (>=0 random symbols)  

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

COMMAND SUBSTITUTION:  
$(commnad) -> open invisible new shell(with copied all variables and thir values) make the calculation and return only result of it  

PROCESS SUBSTITUTION:  
>(command) -> this is replaces with string, which is name of a virtual file representing pipe attached to stdin of command
<(command) -> this is replaces with string, which is name of a virtual file representing pipe attached to stdout of command
examples:
comm -2 -3 <(cat /etc/passwd | cut -d : -f 1 | sort) <(who |cut -d ' ' -f 1 | sort)
whoami | read name
echo "name: ${name}"
name :
WRONG!!!

read name < <(whoami)
echo "name: ${name}"
name : ivan
RIGHT!!!

wc {path} -> returning number of differant things like words, lines, sybols, bytes ec. in given path to file  
tr {Object1} {Object2} -> change object1 with object2(this command should take string from stdin)  
cut -> cutting table data  
sort -> lexicographic sorting  
du -> size of all files  
seq 1 5 -> number from 1 to 5  
uniq -> take string and delete line if two adjacent rows are same.  
comm {file1} {file2} -> print 3 columns. The first column is the unique words from the first file. Second with the second file and third column with the same words.  
mktemp -> create temp file(have to delete it after your work is done)  
cmp -> check if 2 files are equel  
sha256sum -> make hash of file  
diff -> compare two files line by line  
pwgen -> generate password  
set -> show all variables  
examples: 
{name of variable}={value}
name="Ivan Ivanov"
echo "my name is ${name}"

env -> show hole environtment variables table  
export {name of variable}={value} -> for environment variables  
environment variables:  
${SHELL} -> PATH TO THIS SHELL  
${USER} -> USERNAME OF CURRENT USER  
${HOME} -> HOME DIRECTORY OF CURRENT USER  
${PS1} -> STRING WHICH YOU LOGIN (s0600..@astero)
${PATH} -> PATH FOR SEARCHING COMMAND  
${PWD} -> CURRENT DIRECTORY  
${IFS} -> INTERNAL FIELD SEPARATOR  
${EDITOR} -> EDITOR  
${#} -> NUMBER OF PARAMETERS  
${0} -> NAME OF THE CURRENT SCRIPT  
${@}/${*} -> ALL PARAMETERS (SEE THE DIFFERANCE!)  

${?} -> EXIT STATUS OF COMMAND BEFORE  
${!} -> PID OF PROCESS IN BACKGROUND MODE  
which {commnad} -> shows where is this program(command) is located 
bc -> string to in/double  and caluculate  
ps -> show active process  
top -> show information about active process in human readable way  
wait {pid} -> wait process with given pid before continuing  
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
example with reversing of last two symbols:  
sed -E 's/.*(.)(.$)/\2\1/g'  

awk -> programming language  
BEGIN{...}  
END{...}  
$0 -> current line  
$1,$2,$3 .. -> exact column  
NF -> number of columns of current row  
NR -> number of rows read by now  
examples: 
awk '$1 == "ivan"'
awk '{print $2}' 

vim -> editor  
If you are in vim you can pause your vim process by pressing cntr + z 
jobs -> shows all process in our session by numbers  
fg {number} -> turn pause process to active by entering the number from jobs  
vimtutor -> man page helper
yy -> copy  
p -> paste  
w -> word forward  
b -> word back  
gg -> begin of file  

:w -> save changes  
:q -> quit  
:q! -> quit without save  
:wq/:x -> save and quit  
