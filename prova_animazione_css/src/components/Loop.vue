<template>
  <div class="container-video">
    <video muted hwz="on" preload="auto" id="myVideo">
      <source src="static/videos/loop_sostitutivo.mp4" type="video/mp4">
    </video>
    <div id="overlay"></div>
  </div>
</template>
<script>
import JQuery from 'jquery';
let $ = JQuery;

export default {
    methods: {  
        initialize() {
            this.videoLoop = $('#myVideo');
            console.log('wtf dovrei fare il loop');

            this.loopIfEnded();
            this.loadVideo(this.videoLoop.get(0), _ => {
              this.videoLoop.get(0).play();
            });
        },
        loopIfEnded() {
          console.log('loop ended');
          this.videoLoop.get(0).addEventListener('ended', _ => {
            this.videoLoop.get(0).play();
          },false);
        },
        loadVideo(video, videoIsLoaded) {
          console.log('loop ended ??');
          video.currentTime = 0;
          video.load();
           
          video.addEventListener('loadeddata', _ => {
              videoIsLoaded();
          }, false);
        },
    },
    computed: {
      //
    },
    mounted() {
        this.initialize();
    },
    data() {
        return {
          premuto: false,
          playbackRate: 1,
        };
    }
}
</script>