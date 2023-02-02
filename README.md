# ClientInteractServer
通过udp通讯实现跨局域网的实时视频数据转发应用<br>
流程图如下<br>
![image](https://github.com/EdokawaKonan-Latest/ClientInteractServer/blob/main/image/Process.jpg)<br>
目前实现部分为数据转发应用服务端b以及客户端c<br>
目前已经实现功能为<br>
当b接收a的数据到达一定数量时,触发信号,让c对d发送b接收的数据.<br>
当c接收d的数据到达一定数量后,触发信号,让b对a发送c接收的数据.<br>
加入心跳包可实现自动连接功能<br>
现外部客户端a为Linux下的gstream,外部服务端d为模拟网络助手.后续将添加外部服务端a的视频流数据处理功能.<br>
目前视频演示效果<br>
![video](https://github.com/EdokawaKonan-Latest/ClientInteractServer/blob/main/image/%E6%BC%94%E7%A4%BA%E8%A7%86%E9%A2%91.mp4)<br>



