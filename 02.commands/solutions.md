##02-a-0100
mkdir my_passwd
cp /etc/passwd my_passwd

##02-a-0500
mkdir -p practice-test/test1
cd practice-test/test1/
mv ../../test.txt .

##02-a-0600
mkdir -p practice/01/
touch practice/01/f1 practice/01/f2 practice/01/f3
mkdir dir1
cp practice/01/f1 dir1/
cp practice/01/f2 dir1/
cp practice/01/f3 dir1/

##02-a-0601
mkdir dir2
mv practice/01/f2 dir2/numbers

02-a-1200
find -maxdepth 1 -mindepth 1

02-a-4000
touch permissions.txt
chmod 435 ~/permissions.txt                     //    
chmod u=r permissions.txt
chmod g=wx permissions.txt
chmod o=rx permissions.txt

02-a-4100
find -type f -cmin -59

02-a-5000
cp /etc/services ~
cat services

02-a-5200
ln -s /etc/passwd passwd_symlink
or
ln -s /etc/passwd .
mv passwd passwd_symlink

02-a-5400
find /etc -type f -maxdepth 2

02-a-5401
head -n 5 /etc/services

02-a-5402
find /etc -type f -maxdepth 2 -mindepth 2

02-a-5403
find /etc -maxdepth 1 -mindepth 1 -type d

02-a-5500
find /etc -maxdepth 1 -mindepth 1 -type d | tail -n 10 > etcLast10

02-a-5501
find ~ -type f -size +42

02-a-5504
find /tmp -perm /g=w,o=w

моята група????????????

02-a-5505
find -type f -newer practice/01/f1

02-a-5506
find -type f -newer practice/01/f3 -exec rm -i {} \;

02-a-6000
find /bin/ -type l -perm 777

02-a-8000
mkdir myetc
find /etc -type f -perm -u=r,o=r,g=r -exec cp {} myetc \;

02-a-9000
tar -c -f c_start.tar $(find myetc -type f -iname 'c*')
tar -v -t -f c_start.tar

02-a-9500
find /etc -type f -exec wc -l {} \;

02-b-4000
cp $(find /etc -type f -printf '%s %h/%f\n' 2>/dev/null | sort -n | head -n 1 | cut -d ' ' -f 2-) ~ 
