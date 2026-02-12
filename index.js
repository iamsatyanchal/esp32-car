    const $ = id => document.getElementById(id);
    //let client = null;
    let isExecutingCommands = false;

    const SYSTEM_PROMPT = `
    You are an ESP32 RC car controller AI named Xythobot. Convert commands to JSON format.
Available commands: forward, backward, left, right, stop, honk, led_on, led_off, buzzer
IMPORTANT: Always respond with ONLY a JSON array of commands. Each command must have:
- "action": one of the available commands
- "duration": time in seconds (use 0 for instant commands like stop, honk)
Examples:
User: "Go forward for 2 seconds" -> Response: [{"action": "forward", "duration": 2}]
Always respond with valid JSON only.`;



    let deferredPrompt;

    // window.addEventListener('beforeinstallprompt', (e) => {
    //   e.preventDefault();
    //   deferredPrompt = e;
    //   $('installBtn').classList.remove('hidden');
    // });

    // $('installBtn').addEventListener('click', async () => {
    //   if (deferredPrompt) {
    //     deferredPrompt.prompt();
    //     const { outcome } = await deferredPrompt.userChoice;
    //     deferredPrompt = null;
    //     $('installBtn').classList.add('hidden');
    //   }
    // });


function switchPage(pageId) {

    document.querySelectorAll('.nav-item').forEach(item => item.classList.remove('active'));
    document.querySelectorAll('.page').forEach(page => {
        page.classList.remove('page-active');
        page.classList.add('page-hidden');
    });

    const target = $(pageId);
    if (target) {
        target.classList.remove('page-hidden');
        target.classList.add('page-active');
    }
    const navBtn = document.querySelector(`[data-page="${pageId}"]`);
    if (navBtn) {
        navBtn.classList.add('active');
    }
}

document.querySelectorAll('.nav-item').forEach(item => {
    item.addEventListener('click', () => {
        switchPage(item.getAttribute('data-page'));
        if (navigator.vibrate && $('vibrationToggle').checked) {
            navigator.vibrate(10);
        }
    });
});


function setStatus(status, isConnected = false) {
    $('statusText').textContent = status;
   /*$('statusDot').className = 
       `w-2 h-2 rounded-full transition-colors duration-300 ${isConnected 
        ? 
      'bg-green-500 shadow-[0_0_8px_rgba(34,197,94,0.6)]' : 'bg-red-500'}`;*/

    if (isConnected) {
        $('connectBtn').classList.add('hidden');
        $('disconnectBtn').classList.remove('hidden');
        if (!$('connectPage').classList.contains('page-hidden')){
            switchPage('drivePage');
        }
    } else {
        $('connectBtn').classList.remove('hidden');
        $('disconnectBtn').classList.add('hidden');
    }
}

function setAIStatus(s) {
    $('aiStatus').textContent = s;
}


function connect() {
    const broker = $('broker').value.trim();
    setStatus('MAKING', false);
    try {
        client = mqtt.connect(broker, {
            clientId: 'xytho-' + Math.random().toString(16).slice(2, 10),
            clean: true, keepalive: 30
        });
    } catch (e) {
        setStatus('ERROR', false);
        return;
    }
    client.on('connect', () => setStatus('MADE', true));
    client.on('error', (err) => setStatus('ERR', false));
    client.on('close', () => setStatus('REQUIRED', false));
}

function disconnect() {
    if (client) client.end();
    client = null;
    setStatus('REQUIRED', false);
}



function publish(cmd) {
    const topic = $('topic').value.trim();
    if (!client || !client.connected) {
        return false;
    }
    client.publish(topic, cmd);
    $('lastCommand').textContent = '> ' + cmd;
    return true;
}
