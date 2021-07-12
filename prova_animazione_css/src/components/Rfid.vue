<template>
  <div class="container-video">
    <video muted id="openVideo" preload="auto" hwz="on">
      <source src="/static/videos/amarcord.mp4" type="video/mp4">
    </video>
    <video muted hwz="on" preload="auto" id="myVideo">
      <source src="/static/videos/loop.mp4" type="video/mp4">
    </video>
    <div id="overlay"></div>
  </div>
</template>
<script>
import JQuery from 'jquery';
let $ = JQuery;
import { TimelineLite, TweenMax, Quad, TimelineMax } from 'gsap'

export default {
    methods: {  
        initialize() {
            this.videoOpen = $('#openVideo');
            this.videoLoop = $('#myVideo');

            this.loopIfEnded();

            this.videoOpen.css('visibility', 'hidden');
            this.loadVideo(this.videoLoop.get(0), _ => {
              this.videoLoop.get(0).play();
            });

            let keys = this.timeline.map(a => a.code);

            $(document).keypress(e => {
              console.log('code', e.charCode);

              if(keys.includes(e.charCode)) {
                let obj = this.timeline.find(x => x.code === e.charCode);
                console.log(e.charCode, obj);

                if(obj) {
                  if(obj.isLoop == true) {
                    console.log(obj);
                    this.playLoop();
                  } else if(obj.velocity != null) {
                    console.log('dovrei cambiare la velocità');

                    if (obj.velocity == 1) {
                      this.playbackRate = 3;
                      this.videoOpen.get(0).playbackRate = this.playbackRate;
                      console.log('veloce');
                    } else if (obj.velocity == 0) {
                      this.playbackRate = 1;
                      this.videoOpen.get(0).playbackRate = this.playbackRate;
                      console.log('lento');
                    }
                  } else {
                    this.changeSource(obj.src);
                    console.log("the src", obj.src);
                  }
                }
              }
          });
        },
        loopIfEnded() {
          this.videoOpen.get(0).addEventListener('ended', _ => {
            this.videoOpen.get(0).play();
          },false);
          this.videoLoop.get(0).addEventListener('ended', _ => {
            this.videoLoop.get(0).play();
          },false);
        },
        fadeToBlack(isBlack) {
            var tl = new TimelineMax({paused: true});
            tl.to('#overlay', 1, {opacity: 1, onComplete: isBlack});
            tl.delay(1);
            tl.to('#overlay', 1, {opacity: 0});
            tl.play();
        },
        loadVideo(video, videoIsLoaded) {
          video.currentTime = 0;
          video.load();
           
          video.addEventListener('loadeddata', _ => {
              videoIsLoaded();
          }, false);
        },
        changeSource(url) {
          //console.log('quante volte sono entrato?');

          this.videoOpen.css('visibility', 'visible');
          this.videoOpen.get(0).src = url;

          this.loadVideo(this.videoOpen.get(0), _ => {
            console.log('video is loaded');
            this.videoOpen.get(0).playbackRate = this.playbackRate;
            this.doAnimation();
          });
        },
        doAnimation() {
          this.fadeToBlack(_ => {
            this.videoLoop.get(0).pause();
            this.videoOpen.get(0).play();
            this.videoLoop.css('visibility', 'hidden');
          });
        },
        playLoop() {
          this.fadeToBlack(n => {
            this.videoLoop.css('visibility', 'visible');
            this.videoOpen.get(0).pause();
            this.videoOpen.css('visibility', 'hidden');
          });
          
          this.loadVideo(this.videoLoop.get(0), _ => {
            console.log('video is loaded');
            this.videoLoop.get(0).play();
          });
        }
    },
    computed: {
      //
    },
    mounted() {
        this.initialize();
    },
    data() {
        return {
          timeline: [{'code': 65, 'src': '/static/videos/citta_donne.mp4', 'isLoop': false}, {'code': 66, 'src': '/static/videos/clowns.mp4', 'isLoop': false}, {'code': 67, 'src': '/static/videos/amarcord.mp4', 'isLoop': false}, {'code': 76, 'src': '/static/videos/loop.mp4', 'isLoop': true }, {'code': 90, 'velocity': 1}, {'code': 78, 'velocity': 0}],
          premuto: false,
          playbackRate: 1,
        };
    }
}
</script>