<h1>Computer Networks Final Project Fall 2018</h1>
<p>By Garrett Moncrief and Rachel Klesius</p>

<h2>Problem to be solved</h2>
<p>The parameters of the problem are described <a href="http://www.csee.usf.edu/~kchriste/class2/project2.html">on the USF Networks I page</a> and require that port knocking be used to prevent a playback attack and a denial of service attack.</p>

<h2>How to Run</h2>
<p>This program was run on a Windows 10 system using <a href="http://www.mingw.org/">MinGW</a>.</p>
<p>To execute the server use the following commands:  <br>gcc tcpServer.c -lws2_32 -o tcpServer<br>tcpServer</p>
<p>To execute the client use the following commands: <br>gcc tcpClient.c -lws2_32 -o tcpClient<br>tcpClient</p>