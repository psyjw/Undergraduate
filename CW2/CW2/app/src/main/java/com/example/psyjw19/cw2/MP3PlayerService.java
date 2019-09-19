package com.example.psyjw19.cw2;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.os.Build;
import android.support.v4.app.NotificationCompat;
import android.app.PendingIntent;

public class MP3PlayerService extends Service {

    private MP3Player mp3Player;
    private final String CHANNEL_ID = "100";
    private NotificationCompat.Builder mBuilder;
    private String musicName = null;
    private String musicState = null;
    private int NOTIFICATION_ID = 001;
    private NotificationManager notificationManager;

    private final IBinder binder = new MyBinder();
    @Override
    public void onCreate() {
        super.onCreate();

        mp3Player = new MP3Player();
        notificationManager = (NotificationManager)
                getSystemService(NOTIFICATION_SERVICE);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            CharSequence name = "channel name";
            String description = "channel description";
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, name,
                    importance);
            channel.setDescription(description);
            channel.setSound(null, null);
            // Register the channel with the system; you can't change the importance
            // or other notification behaviors after this
            notificationManager.createNotificationChannel(channel);
        }

        Intent intent = new Intent(this, MainActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, intent, 0);
        mBuilder = new NotificationCompat.Builder(this,
                CHANNEL_ID)
                .setSmallIcon(R.drawable.ic_launcher_background)
                .setContentIntent(pendingIntent)
                .setPriority(NotificationCompat.PRIORITY_DEFAULT)
                .setSound(null);

        setNotification();
        notificationManager.notify(NOTIFICATION_ID, mBuilder.build());

    }

    public void setNotification() {
        if (mp3Player.state == MP3Player.MP3PlayerState.PAUSED) {
            musicName = mp3Player.filePath.replace("/storage/emulated/0/Music/", "");
            musicState = "Paused";
        }
        else if (mp3Player.state == MP3Player.MP3PlayerState.PLAYING) {
            musicName = mp3Player.filePath.replace("/storage/emulated/0/Music/", "");
            musicState = "Playing";
        }
        else {
            musicName = "MP3Player";
            musicState = "No music playing";
        }
        mBuilder.setContentTitle(musicName);
        mBuilder.setContentText(musicState);
    }

    @Override
    public IBinder onBind(Intent arg0) {
        return new MyBinder();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d("CW2", "service onStartCommand");
        return Service.START_STICKY;
    }

    @Override
    public void onDestroy() {
        Log.d("CW2", "service onDestroy");
        this.stop();
        notificationManager.cancelAll();
        super.onDestroy();
    }

    public class MyBinder extends Binder
    {
        void play() {
            MP3PlayerService.this.play();
        }
        void pause() {
            MP3PlayerService.this.pause();
        }
        void stop() {
            MP3PlayerService.this.stop();
        }
        void load(String filePath) {
            MP3PlayerService.this.load(filePath);
        }
        int getDuration() {
            return MP3PlayerService.this.getDuration();
        }
        int getProgress() {
            return MP3PlayerService.this.getProgress();
        }
        void quit() {MP3PlayerService.this.quit();}
    }

    public void play() {
        mp3Player.play();
        setNotification();
        notificationManager.notify(NOTIFICATION_ID, mBuilder.build());
    }

    public void pause() {
        mp3Player.pause();
        setNotification();
        notificationManager.notify(NOTIFICATION_ID, mBuilder.build());
    }

    public void stop() {
        mp3Player.stop();
        setNotification();
        notificationManager.notify(NOTIFICATION_ID, mBuilder.build());
    }

    public void load(String filePath) {
        mp3Player.load(filePath);
        setNotification();
        notificationManager.notify(NOTIFICATION_ID, mBuilder.build());
    }

    public int getDuration() {
        return mp3Player.getDuration();
    }

    public int getProgress() {
        return mp3Player.getProgress();
    }

    public void quit() {this.stopSelf();}

    @Override
    public void onRebind(Intent intent) {
        super.onRebind(intent);
    }

    @Override
    public boolean onUnbind(Intent intent) {
        return super.onUnbind(intent);
    }
}
