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
