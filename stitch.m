
%% Image stuitching

I1 = imread('1.jpg');
I2 = imread('2.jpg');
I1_gray = rgb2gray(I1);
I2_gray = rgb2gray(I2);

% Compute the features for each we use SURF algorithms

points1 = detectSURFFeatures(I1_gray);
[features1, points1] = extractFeatures(I1_gray, points1);


points2 = detectSURFFeatures(I2_gray);
[features2, points2] = extractFeatures(I2_gray, points2);

%matching the features
indexPairs = matchFeatures(features1, features2);

matchedPoints1 = points1(indexPairs(:,1), :);
matchedPoints2 = points2(indexPairs(:,2), :);

% estimate the transform

trnsfrm = estimateGeometricTransform(matchedPoints1, matchedPoints2,...
        'projective', 'Confidence', 99.9, 'MaxNumTrials', 2000);

blender = vision.AlphaBlender('Operation', 'Binary mask', ...
    'MaskSource', 'Input port');

% Now the stitch
[xlim1, ylim1] = outputLimits(trnsfrm, [1 size(I1,2)], [1 size(I1,1)]);
xMin = min([1; xlim1(:)]);
xMax = max([size(I1,2); xlim1(:)]);

yMin = min([1; ylim1(:)]);
yMax = max([size(I1,1); ylim1(:)]);

% Width and height of panorama.
width  = round(xMax - xMin);
height = round(yMax - yMin);
panorama = zeros([height width 3], 'like', I1);
xLimits = [xMin xMax];
yLimits = [yMin yMax];
panoramaView = imref2d([height width], xLimits, yLimits);

% H = invert(trnsfrm);
H = trnsfrm;
warpedImage1 = imwarp(I1,H,'OutputView',panoramaView);
H.T = [1,0,0;0,1,0;0,0,1];
warpedImage2 = imwarp(I2,H,'OutputView',panoramaView);
% panaroma = zeros(max(size(I1,1),size(I2,1)),size(I1,2) + size(I2,2),3);
panorama = step(blender, panorama, warpedImage1, warpedImage1(:,:,1));
panorama = step(blender, panorama, warpedImage2, warpedImage2(:,:,1));

imshow(panorama);