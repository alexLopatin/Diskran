./KP.exe $args[0] $args[2] $args[3] $args[4] $args[5]
if(Test-Path out.map) {
	./Visualizer.exe out.map $args[1]
	Remove-Item out.map
	start $args[1]
}
Write-Output 'Script execution ended.'