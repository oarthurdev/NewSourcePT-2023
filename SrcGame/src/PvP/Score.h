#ifndef SCORE_H
#define SCORE_H

class Score
{
private:

public:
	Score();
	~Score();


	void sendAlert();


	bool draw();
	bool drawZone();
	bool drawScore();
	bool drawImgPVP();
};

#endif
