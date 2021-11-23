#include "ProgressDialog.h"
#include "QBoxLayout"
#include <QProgressBar>
#include "QLabel"

ProgressDialog::ProgressDialog(const QString& title, QWidget *parent) : BaseDialog(title,parent)
{
	initUI();
}

void ProgressDialog::onInfoTextChanged(const QString& text)
{
	infoLabel_->setText(text);
}

void ProgressDialog::onFinished()
{
	accept();
}

void ProgressDialog::initUI()
{
	setFixedSize(400, 200);
	setObjectName("progressDialog");

	auto mainLayout = qobject_cast<QVBoxLayout*>(this->layout());

	QFrame* centerFrame_ = new QFrame(this);
	centerFrame_->setFrameShape(QFrame::Shape::NoFrame);
	centerFrame_->setObjectName("centerFrame");

	QVBoxLayout* centerLayout_ = new QVBoxLayout();
	centerLayout_->setSpacing(6);
	centerLayout_->setMargin(0);
	centerLayout_->setAlignment(Qt::AlignCenter);
	centerLayout_->setContentsMargins(20, 6, 20, 6);
	centerFrame_->setLayout(centerLayout_);
	mainLayout->addWidget(centerFrame_);

	progressBar_ = new QProgressBar(this);
	progressBar_->setObjectName("progressBar");
	progressBar_->setMaximum(0);
	progressBar_->setMinimum(0);
	progressBar_->setOrientation(Qt::Horizontal);  // 水平方向
	centerLayout_->addWidget(progressBar_);

	infoLabel_ = new QLabel(this);
	infoLabel_->setObjectName("infoLabel");
	infoLabel_->setWordWrap(true);
	infoLabel_->adjustSize();

	centerLayout_->addWidget(infoLabel_);
}
