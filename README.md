<h1>Computer Networks Final Project Fall 2018</h1>
<p>By Garrett Moncrief and Rachel Klesius</p>

<h2>Problem to be solved</h2>
<p>The parameters of the problem are described <a href="http://www.csee.usf.edu/~kchriste/class2/project2.html">on the USF Networks I page</a> and require that port knocking be used to prevent a playback attack and a denial of service attack.</p>

<h2>How to Run</h2>
<p>This program was run on a Windows 10 system using <a href="http://www.mingw.org/">MinGW</a>.</p>
<p>
   To execute the server use the following commands:  
   <code>mingw32-make server</code><br><code>server</code>
</p>
<p>
   To execute the client use the following commands: 
    <code>mingw32-make client</code><br><code>client</code>
</p>

<h2>System Setup</h2>
<p>Requires two PCs: one as client and one as the server.
<br>Server needs the knock_server and web_server along with the three html test files and a large data file</p>