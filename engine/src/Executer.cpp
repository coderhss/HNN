#include "Executer.h"
#include <fstream>
namespace HNN {

    ErrorCode Executer::input(std::string name, TensorPtr& tensor) {
        uint32_t blobIndex = net->getIndexFromBlobName(name);
        if (blobIndex == -1) {
            LOG_E("can not find blob: ", name);
            return ErrorCode::NN_FAILED;
        }
        featureMaps[blobIndex] = tensor;
        return ErrorCode::NN_OK;
    }

    ErrorCode Executer::forward() {
        return ErrorCode::NN_OK;
    }

    ErrorCode Executer::getBlob(std::string blobName, TensorPtr& tensor, Config& config) {
        uint32_t blobIndex = net->getIndexFromBlobName(blobName);
        if (blobIndex == -1) {
            LOG_E("can not find blob: ", blobName);
            return ErrorCode::NN_FAILED;
        }

        if (featureMaps.at(blobIndex) != nullptr) {
            tensor = featureMaps[blobIndex];
            return ErrorCode::NN_OK;
        }

        BlobPtr blob = net->blobs.at(blobIndex);
        if (blob == nullptr) {
            LOG_E("can not find blob: {}, at: {}", blobName, blobIndex);
            return ErrorCode::NN_FAILED;
        }
        uint32_t layerIndex = blob->producer;
        dfsForword(layerIndex, config);

        if (featureMaps.at(blobIndex) != nullptr) {
            tensor = featureMaps[blobIndex];
            return ErrorCode::NN_OK;
        }
        return ErrorCode::NN_FAILED;
    }

    ErrorCode Executer::dfsForword(uint32_t layerIndex, Config& config) {
        LayerPtr layer = net->getLayerFromIndex(layerIndex);
        if (layer == nullptr) {
            LOG_E("layer is nullptr.");
            return ErrorCode::NN_FAILED;
        }
        for (uint32_t i = 0; i < layer->bottoms.size(); ++i) {
            uint32_t blobIndex = layer->bottoms[i];
            TensorPtr tensor = featureMaps[blobIndex];
            if (tensor == nullptr) {
                BlobPtr blob = net->getBlobFromIndex(blobIndex);
                ErrorCode errorCode = dfsForword(blob->producer, config);
                if (errorCode != ErrorCode::NN_OK) {
                    return errorCode;
                }
            }   
        }
        std::vector<TensorPtr> input;
        for (uint32_t i = 0; i < layer->bottoms.size(); ++i) {
            input.emplace_back(featureMaps[layer->bottoms[i]]);
        }
        
        std::vector<TensorPtr> output;
        for (uint32_t i = 0; i < layer->tops.size(); ++i) {
            output.emplace_back(featureMaps[layer->tops[i]]);
        }
        // for (uint32_t i = 0; i < input.size(); ++i) {
        //     LOG_E("n: {}, c: {}, h: {}, w: {}", input[i]->getShape()[0], input[i]->getShape()[1], input[i]->getShape()[2], input[i]->getShape()[3]);
        // }
        auto result = layer->inference(input, output, config);
        for (uint32_t i = 0; i < layer->tops.size(); ++i) {
            output[i]->mName = net->getBlobFromIndex(layer->tops[i])->name;
            featureMaps[layer->tops[i]] = output[i];
        }
        return result;
    }

    ErrorCode Executer::dumpAllTensor(std::string& path) {
        uint32_t size = featureMaps.size();
        for (uint32_t i = 0; i < size; ++i) {
            auto tensor = featureMaps[i];
            LOG_E("save: {}, {}", i, tensor->mName);
            if (tensor != nullptr) {
                // auto layer = net->getLayerFromIndex(i);
                std::ofstream outfile;
                std::string outPath;
                std::string fileName  = "";
                for (uint32_t i = 0; i < tensor->mName.size(); ++i) {
                    if (tensor->mName[i] == '/') {
                        fileName += '%';
                    } else {
                        fileName += tensor->mName[i];
                    }
                }
                LOG_E("real save: {}", fileName);
                if (path.back() == '/') {
                    outPath = path + fileName + ".txt";
                } else {
                    outPath = path + '/' + fileName + ".txt";
                }

                outfile.open(outPath, std::ios::out | std::ios::trunc);
                auto shape = tensor->getShape();
                float* data = tensor->getData<float>();
                uint32_t N = shape[0], C = shape[1], H = shape[2], W = shape[3];
                LOG_E("N: {}, C: {}, H: {}, W: {}", N, C, H, W);
                for (uint32_t n = 0; n < N; ++n) {
                    for (uint32_t c = 0; c < C; ++c) {
                        outfile << "N: " << n << " " << "C: " << c << std::endl;
                        for (uint32_t h = 0; h < H; ++h) {
                            for (uint32_t w = 0; w < W; ++w) {
                                outfile << data[n * (C * H * W) + c * (H * W) + h * W + w] << " ";
                            }
                            outfile << std::endl;
                        }
                        outfile << std::endl;
                    }
                }
            }
        }
    }

} // namespace name