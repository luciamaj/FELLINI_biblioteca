<template>
  <div class="container-video">
    <video hwz="on" preload="auto" id="myVideo">
      <source :src="dataApp[0]" type="video/mp4">
    </video>
    <div id="overlay"></div>
    <Tsunami :isVisible="false" @tsunamiStarted="freeze" @tsunamiEnded="restart"/>
  </div>
</template>
<script>

import JQuery from 'jquery';
import { TimelineLite, TweenMax, Quad, TimelineMax } from 'gsap'
import Tsunami from './Tsunami.vue';
let $ = JQuery;

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
          this.fadeToBlack(_ => {
            this.videoLoop.get(0).pause();
            this.$emit('startTsunami');
          });
        },
        restart() {
          console.log("restart??");

          this.fadeFromBlack(_ => {
            console.log("cosa deve partire?", this.isPlayingLoop);
            this.videoLoop.get(0).play();
          });
        },
        initialize() {
          this.videoLoop = $('#myVideo');

          this.changeVidIfEnded();

          if(this.videoLoop.get(0)) {
            this.loadVideo(this.videoLoop.get(0), _ => {
              this.videoLoop.get(0).play();
            });
          } else {
            console.log("is empty");
          }
        },
        changeVidIfEnded() {
          this.videoLoop.get(0).addEventListener('ended', _ => {
            console.log("current index", this.currentIndex);
            console.log("data app", this.dataApp);
            if (this.currentIndex < this.dataApp.length - 1) {
              this.currentIndex++;
            } else {
              print("dovrei ripartire");
              this.currentIndex = 0;
            }

            let url = this.dataApp[this.currentIndex].src;
            
            this.changeSource(url);
            console.log("I'M CHANN");
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
          this.videoLoop.get(0).src = url;

          this.loadVideo(this.videoLoop.get(0), _ => {
            this.videoLoop.get(0).play();
            this.doAnimation();
          });
        },
        doAnimation() {
          this.fadeToBlackBack(_ => {
            this.videoLoop.get(0).play();
          });
        }
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
          currentIndex: 0,
        };
    }
}
</script>