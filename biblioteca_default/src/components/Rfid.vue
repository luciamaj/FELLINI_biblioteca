<template>
  <div class="container-video">
    <video id="openVideo" preload="auto" hwz="on">
      <source :src="'../assets/schede/amarcord1.mp4'" type="video/mp4">
    </video>
    <video hwz="on" preload="auto" id="myVideo" autoplay muted>
      <source :src="'../assets/loop.mp4'" type="video/mp4">
    </video>
    <div id="overlay"></div>
    <Tsunami :isVisible="false" @tsunamiStarted="freeze" @tsunamiEnded="restart"/>
  </div>
</template>
<script>
import JQuery from 'jquery';
let $ = JQuery;
import { TimelineLite, TweenMax, Quad, TimelineMax } from 'gsap'
import Tsunami from './Tsunami.vue';

export default {
    components: { Tsunami },
    methods: {
        fadeToBlackBack(isBlack) {
          var tl = new TimelineMax({paused: true});
          tl.to('#overlay', 0.5, {autoAlpha: 1, onComplete: isBlack});
          tl.delay(0.5);
          tl.to('#overlay', 0.5, {autoAlpha: 0});
          tl.play()
        },
        fadeFromBlack(isBlack) {
          var tl = new TimelineMax({paused: true});
          tl.to('#overlay', 0.5, {autoAlpha: 0, onComplete: isBlack});
          tl.play()
        },
        fadeToBlack(isBlack) {
          var tl = new TimelineMax({paused: true});
          tl.to('#overlay', 0.5, {autoAlpha: 1, onComplete: isBlack});
          tl.play()
        },
        freeze() {
          this.tsunamiPlaying = true;
          this.fadeToBlack(_ => {
            console.log("IS PLAYNG LOOP?", this.isPlayingLoop);
            if (this.isPlayingLoop) {
              this.videoLoop.get(0).pause();
            } else {
              console.log("lo sto mettendo in pausa?");
              this.videoOpen.get(0).pause();
            }
            this.$emit('startTsunami');
          });
        },
        restart() {
          this.tsunamiPlaying = false;
          this.fadeFromBlack(_ => {
            console.log("IS PLAYNG LOOP?", this.isPlayingLoop);
            if (this.isPlayingLoop) {
              this.videoLoop.get(0).play();
              this.videoOpen.get(0).pause();
            } else {
              this.videoOpen.get(0).play();
              this.videoLoop.get(0).pause();
            }
          });
        },
        initialize() {
            if (true) {
              this.videoOpen = $('#openVideo');
              this.videoLoop = $('#myVideo');

              this.loopIfEnded();

              this.videoOpen.css('visibility', 'hidden');
              this.loadVideo(this.videoLoop.get(0), _ => {
                this.videoLoop.get(0).play();
              });

              let keys = this.dataApp.map(a => a.code);

              $(document).keypress(e => {
                if(keys.includes(e.charCode)) {
                  let obj = this.dataApp.find(x => x.code === e.charCode);
                  console.log(e.charCode, obj);

                  if(obj) {
                    if(obj.isLoop == true) {
                      if(this.isPlayingLoop != true) {
                        this.src = "loop"
                        console.log(obj);
                        this.playLoop();
                        this.isPlayingLoop = true;
                      } else {
                        console.log("sono già nel loop");
                      }
                    } else if(obj.velocity != null) {
                      console.log('dovrei cambiare la velocità');

                      if (obj.velocity == 1) {
                        this.playbackRate = obj.playbackRate;
                        this.videoOpen.get(0).playbackRate = this.playbackRate;
                        console.log('veloce');
                      } else if (obj.velocity == 0) {
                        this.playbackRate = obj.playbackRate;
                        this.videoOpen.get(0).playbackRate = this.playbackRate;
                        console.log('lento');
                      }
                    } else {
                      if (this.src != obj.src) {
                        this.src = obj.src;
                        this.changeSource(obj.src);
                        console.log("the src", obj.src);
                        this.isPlayingLoop = false;
                      } else {
                        console.log("ho cercato di riaprire lo stesso video");
                      }
                    }
                  }
                }
            });
          }
        },
        loopIfEnded() {
          // IF OPEN VIDEO STOPPED PLAY LOOP
          this.videoOpen.get(0).addEventListener('ended', _ => {
            this.src = "loop"
            this.playLoop();
            this.isPlayingLoop = true;
          },false);
          
          // IF VIDEO LOOP STOPPED LOOP LOOP
          this.videoLoop.get(0).addEventListener('ended', _ => {
            this.videoLoop.get(0).play();
          },false);
        },
        loadVideo(video, videoIsLoaded) {
          video.currentTime = 0;
          video.load();
           
          video.addEventListener('loadeddata', _ => {
              videoIsLoaded();
          }, false);
        },
        changeSource(url) {
          this.videoOpen.css('visibility', 'visible');
          this.videoOpen.get(0).src = url;

          this.loadVideo(this.videoOpen.get(0), _ => {
            console.log('video is loaded');
            this.videoOpen.get(0).playbackRate = this.playbackRate;
            this.doAnimation();
          });
        },
        doAnimation() {
          this.fadeToBlackBack(_ => {
            if (!this.tsunamiPlaying) {
              this.videoLoop.get(0).pause();
              this.videoOpen.get(0).play();
              this.videoLoop.css('visibility', 'hidden');
            }
          });
        },
        playLoop() {
          this.fadeToBlackBack(_ => {
            this.videoLoop.css('visibility', 'visible');
            this.videoOpen.get(0).pause();
            this.videoOpen.css('visibility', 'hidden');
          });
          
          this.loadVideo(this.videoLoop.get(0), _ => {
            console.log('video is loaded');
            this.videoLoop.get(0).play();
          });
        },
    },
    computed: {
      dataApp() {
        console.log(this.$store.getters.data.timeline);
        return this.$store.getters.data.timeline;
      }
    },
    mounted() {
      this.initialize();
    },
    data() {
        return {
          premuto: false,
          playbackRate: 1,
          tsunamiPlaying: false,
          isPlayingLoop: true,
        };
    },
}
</script>