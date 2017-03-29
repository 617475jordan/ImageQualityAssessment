#include "ImageQualityAssessment.h"
#include "APIofIQA.h"
#include <ctime>

int main(int argc,char** argv){
	String reference = "test//10.png";
	String  source = "test//result.png";
	Mat referenceImage = imread(reference, 0);
	Mat sourceImage = imread(source, 0);
	if (referenceImage.empty() || sourceImage.empty())
	{
		cout << "out" << endl;
		
		return -1;

	}
	ImageQualityAssessment ssim = ImageQualityAssessment(referenceImage, sourceImage);
	clock_t ss = clock();
	double old_ssim = ssim.ssim();
	cout << "ssim: "<<old_ssim << endl;
	clock_t ee = clock();
	double old_ssim_cost = (double)(ee - ss) / 1000;
	cout << "old_ssim_cost: " << old_ssim_cost<<"s"<< endl;
	ss = clock();
	double psnr=ssim.psnr();
	cout << "psnr: " << psnr << endl;
	ee = clock();
	double psnr_cost = (double)(ee - ss) / 1000;
	cout << "psnr_cost: " << psnr_cost << "s" << endl;
	ssim.blockSize = 11;

	ss = clock();
	double new_ssim = ssim.ssim(referenceImage, sourceImage);
	cout << "new_ssim: " << new_ssim << endl;
	ee = clock();
	double new_ssim_cost = (double)(ee - ss) / 1000;
	cout << "new_ssim_cost: " << new_ssim_cost << "s" << endl;

	double Hash = ssim.hashDistance();
	double Dhash = ssim.DhashDistance();
	double Phash = ssim.PhashDistance();
	double Iqa = IQA(referenceImage, sourceImage);
	double win_ssim = blockIQA(referenceImage, sourceImage, 2);
	cout << "Hash: " << Hash << endl;
	cout << "Dhash: " << Dhash << endl;
	cout << "Phash: " << Phash << endl;
	cout << "IQA: " << Iqa << endl;
	cout << "win_ssim: " << win_ssim << endl;
	//cout << ssim.sigma(referenceImage, 0, 0) << endl;
	cout << "数据保存" << endl;
	FileStorage file;
	file.open("IQAData0.xml", FileStorage::WRITE);
	file << "old_ssim" << old_ssim;
	file << "old_ssim_cost" << old_ssim_cost;
	file << "new_ssim" << new_ssim;
	file << "new_ssim_cost" << new_ssim_cost;
	file << "Hash" << Hash;
	file << "Dhash" << Dhash;
	file << "Phash" << Phash;
	file << "IQA" << Iqa;
	file << "win_ssim" << win_ssim;
	file.release();
	cout << "数据保存完毕" << endl;
	waitKey();
	while (1);
	return 0;
}