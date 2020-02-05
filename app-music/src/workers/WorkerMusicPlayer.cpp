#include "workers/WorkerMusicPlayer.h"

WorkerMusicPlayer::WorkerMusicPlayer()
{
	m_bIsWorkerInitialized = false;

	init();
}

WorkerMusicPlayer::~WorkerMusicPlayer()
{
	
}

void WorkerMusicPlayer::doWork()
{

}

bool WorkerMusicPlayer::init()
{
	

	return m_bIsWorkerInitialized;
}

void WorkerMusicPlayer::setSignalValues(std::vector<float> vSignalValues)
{

}

void WorkerMusicPlayer::play()
{
    // initialize parameters
    qreal sampleRate = 40000;   // sample rate
    qreal duration = 1.000;     // duration in seconds
    qreal frequency = 1000;     // frequency
    const quint32 n = static_cast<quint32>(duration * sampleRate);   // number of data samples

    // --- transfer QVector data to QByteBuffer
    QByteArray* byteBuffer = new QByteArray();  // create a new instance of QByteArray class (in the heap, dynamically arranged in memory), and set its pointer to byteBuffer
    byteBuffer->resize(sizeof(float) * n);  // resize byteBuffer to the total number of bytes that will be needed to accommodate all the n data samples that are of type float

    for (quint32 i = 0; i < n; i++)
    {
        qreal sinVal;
        //qreal sinVal = (qreal)qSin(2.0 * M_PI * frequency * i / sampleRate);  // create sine wave data samples, one at a time

        // break down one float into four bytes
        float sample = (float)sinVal;  // save one data sample in a local variable, so I can break it down into four bytes
        char* ptr = (char*)(&sample);  // assign a char* pointer to the address of this data sample
        char byte00 = *ptr;         // 1st byte
        char byte01 = *(ptr + 1);   // 2nd byte
        char byte02 = *(ptr + 2);   // 3rd byte
        char byte03 = *(ptr + 3);   // 4th byte

        // put byte data into QByteArray, one byte at a time
        (*byteBuffer)[4 * i] = byte00;       // put 1st byte into QByteArray
        (*byteBuffer)[4 * i + 1] = byte01;   // put 2nd byte into QByteArray
        (*byteBuffer)[4 * i + 2] = byte02;   // put 3rd byte into QByteArray
        (*byteBuffer)[4 * i + 3] = byte03;   // put 4th byte into QByteArray
    }

    // create and setup a QAudioFormat object
    QAudioFormat audioFormat;
    audioFormat.setSampleRate(static_cast<int>(sampleRate));
    audioFormat.setChannelCount(1);
    audioFormat.setSampleSize(32);   // set the sample size in bits. We set it to 32 bis, because we set SampleType to float (one float has 4 bytes ==> 32 bits)
    audioFormat.setCodec("audio/pcm");
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setSampleType(QAudioFormat::Float);   // use Float, to have a better resolution than SignedInt or UnSignedInt

    // create a QAudioDeviceInfo object, to make sure that our audioFormat is supported by the device
    QAudioDeviceInfo deviceInfo(QAudioDeviceInfo::defaultOutputDevice());
    if (!deviceInfo.isFormatSupported(audioFormat))
    {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    // Make a QBuffer with our QByteArray
    QBuffer* input = new QBuffer(byteBuffer);
    input->open(QIODevice::ReadOnly);   // set the QIODevice to read-only

    // Create an audio output with our QAudioFormat
    QAudioOutput* audio = new QAudioOutput(audioFormat, this);

    // connect up signal stateChanged to a lambda to get feedback
    connect(audio, &QAudioOutput::stateChanged, [audio, input](QAudio::State newState)
        {
            if (newState == QAudio::IdleState)   // finished playing (i.e., no more data)
            {
                qDebug() << "finished playing sound";
                delete audio;
                delete input;
                //delete byteBuffer;  // I tried to delete byteBuffer pointer (because it may leak memories), but got compiler error. I need to figure this out later.
            }
            // should also handle more states, e.g., errors. I need to figure out on how to do this later.
        });

    // start the audio (i.e., play sound from the QAudioOutput object that we just created)
    audio->start(input);
}


